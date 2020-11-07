#ifndef MAPEDITOR_HPP_INCLUDED
#define MAPEDITOR_HPP_INCLUDED

#include "button.hpp"
#include "textBox.hpp"
#include "gui.hpp"
#include "sprite.hpp"
#include "collision.hpp"
#include <unordered_map>

/**********************************************************************************************
*																							  *
* ~ MapEditor ~																				  *
*																							  *
* In order to use the level editor,										                      *
* you have to create a MapEditor object then call the (void) load method					  *
*																							  *
* => MapEditor editor;																		  *
*    editor.load();																			  *
*																							  *
*  In the editor (control) :																  *
*     -> Left Shift => Close the palete														  *
*	  -> Left Control => Open the palete													  *
*	  -> LCTRL + LS => Save by creating a new file (according to the level name entered)      *
*		 -> Saved in a .txt	file														      *
*																							  *
* /!\ BUG : if the user does not enter integers it causes the editor to crash                 *
*																							  *
**********************************************************************************************/

/***** MapEditorGUI *****/

class MapEditorGUI : public GUI {

public:

	MapEditorGUI() = delete;
	MapEditorGUI(Window& window);
	virtual ~MapEditorGUI() = default;

	void handleInputs(InputManager& input, Window& window);

	void convertData(Vector2u& numberSheet, Vector2u& numberTiles, std::string& nameStr, std::string& pathStr, bool& succeed);

	bool buttonState(InputManager& input, Window& window);

private:

	struct GUIObjects {

		TextBox name{ TextBox::Type::LongThin };
		TextBox path{ TextBox::Type::LongThin };
		TextBox numberXSheet{ TextBox::Type::Thin };
		TextBox numberYSheet{ TextBox::Type::Thin };
		TextBox numberXTiles{ TextBox::Type::Thin };
		TextBox numberYTiles{ TextBox::Type::Thin };

		RectButton loadButton{ "Load", Vector2f(140,45), Color::Red };
	};

	GUIObjects guiObjects_;

	void buildGui(); // Constructs the style of the widgets of the GUI
};

/***** MapEditorPalete *****/

class MapEditorPalete : NonCopyable {

public:

	MapEditorPalete() = default;

	virtual ~MapEditorPalete() = default;

	void loadPalete(const Vector2u& numberTiles, const std::string& path);

	void handleClick(InputManager& input, Sprite& currentSprite, int& currentKey);

	SpriteSheet getPaleteSprite() const;

	void drawSheetPalete();

	inline bool isOpen() const; // Tells if the palete is open (sf::RenderWindow object)

	static inline bool isClosed(Event& event);

	inline bool isEvent(Event& event);

	void close();

private:

	SpriteSheet sheet_{ "ress2/tilesMap.png", Vector2u(1,1) };

	std::unordered_map<int, Sprite> sprites_; // A sprite is associated with a key (tile mapping) : for instance the first tile in the sheet has the key 0
	sf::RenderWindow paleteWindow_;

	void mappingPalete(); // Set the tiles representing the palete
};

/***** MapEditor *****/

class MapEditor : NonCopyable {

public:

	MapEditor();
	virtual ~MapEditor() = default;

	void load();

private:

	struct Data {

		Vector2u numberSheet{ 1,1 };
		Vector2u numberTiles{ 1,1 };
		std::string path{ "ress/tilesMap.png" }; // Default path sheet
		std::string name{};
		bool buttonClicked{ false };
	};

	Data data_;

	/* The Camera object will be useful later in order to use views during the level building */

	Camera camera_{}; // TODO
	Window window_{ Vector2u(420,420), "Editor", camera_ };

	MapEditorGUI gui_{ window_ };
	MapEditorPalete palete_;

	std::vector<Sprite> sprites_;
	Matrix<int> mapMatrix_;

	Sprite currentSprite_;
	int currentKey_;

	void loadData(bool& succeed);

	void mapping();

	void handleInputs(InputManager& input, bool& succeed);

	void changeTile(const Vector2u& index);

	static inline Vector2u positionToIndex(const Vector2f& position, const MapEditorPalete& palete);

	static bool const save(const std::string& fileName, const std::string& pathTexture, const Vector2u& numberTilesSheet, const Vector2u& numberTiles, const  Matrix<int>& mapMatrix);

	void drawMap(Window& window);
};

#endif // MAPEDITOR_HPP_INCLUDED