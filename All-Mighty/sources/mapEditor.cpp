#include "mapEditor.hpp"
#include <iostream>

/* MapEditorGUI */

am::MapEditorGUI::MapEditorGUI(Window& window) : GUI(GUI::Style::Center, window) {

	buildGui();

	add("A", guiObjects_.name);
	add("B", guiObjects_.path);
	add("C", guiObjects_.numberXTiles);
	add("D", guiObjects_.numberYTiles);
	add("E", guiObjects_.numberXSheet);
	add("F", guiObjects_.numberYSheet);
	add("G", guiObjects_.loadButton);
}

void am::MapEditorGUI::buildGui() {

	guiObjects_.name.setTextString("Level Name");
	guiObjects_.name.setOutline(3, Color::Yellow);

	guiObjects_.path.setTextString("Path");
	guiObjects_.path.setOutline(3, Color::Yellow);

	guiObjects_.numberXSheet.setTextString("Tiles x in sheet");
	guiObjects_.numberXSheet.setOutline(3, Color::Yellow);

	guiObjects_.numberYSheet.setTextString("Tiles y in sheet");
	guiObjects_.numberYSheet.setOutline(3, Color::Yellow);

	guiObjects_.numberXTiles.setTextString("Number tiles x");
	guiObjects_.numberXTiles.setOutline(3, Color::Yellow);

	guiObjects_.numberYTiles.setTextString("Number tiles y");
	guiObjects_.numberYTiles.setOutline(3, Color::Yellow);

	guiObjects_.loadButton.setOutline(3, Color::Yellow);
	guiObjects_.loadButton.setTextStyle(25, "ress/arial.ttf", Color::Green);

}

void am::MapEditorGUI::handleInputs(InputManager& input, Window& window) {

	guiObjects_.name.manageTextEntered(input, window);
	guiObjects_.path.manageTextEntered(input, window);
	guiObjects_.numberXSheet.manageTextEntered(input, window);
	guiObjects_.numberYSheet.manageTextEntered(input, window);
	guiObjects_.numberXTiles.manageTextEntered(input, window);
	guiObjects_.numberYTiles.manageTextEntered(input, window);
}

void am::MapEditorGUI::convertData(Vector2u& numberSheet, Vector2u& numberTiles, std::string& nameStr, std::string& pathStr, bool& succeed) {

	/* std::stoul could throw an exception */

	try {

		numberSheet.x = std::stoul(guiObjects_.numberXSheet.getText());
		numberSheet.y = std::stoul(guiObjects_.numberYSheet.getText());
		numberTiles.x = std::stoul(guiObjects_.numberXTiles.getText());
		numberTiles.y = std::stoul(guiObjects_.numberYTiles.getText());

		pathStr = guiObjects_.path.getText();
		nameStr = guiObjects_.name.getText();

		succeed = true; // The conversion has been successfully completed
	}

	catch (const std::invalid_argument& error) {

		std::cerr << error.what() << std::endl;
	}

	catch (const std::exception& error) {

		std::cerr << error.what() << std::endl;
	}
}

bool am::MapEditorGUI::buttonState(InputManager& input, Window& window) {

	return guiObjects_.loadButton.isClicked(input, window);
}

/* MapEditorPalete */

void am::MapEditorPalete::loadPalete(const Vector2u& numberTilesSheet, const std::string& path) {

	sheet_.setNewSheet(path, numberTilesSheet);

	paleteWindow_.close();

	paleteWindow_.create(sf::VideoMode(numberTilesSheet.x * sheet_.getSizeOneSprite().x,
									   numberTilesSheet.y * sheet_.getSizeOneSprite().y), "Palete", sf::Style::Titlebar);

	/* Potentially resize the window later */

	mappingPalete();
}

am::SpriteSheet am::MapEditorPalete::getPaleteSprite() const {

	return sheet_;
}

void am::MapEditorPalete::handleClick(InputManager& input, Sprite& currentSprite, int& currentKey) {

	if (input.clickLeft()) {

		for (const auto& i : sprites_) {

			if (Collision::intersectMouse(i.second, paleteWindow_)) {
				currentSprite = i.second;
				currentKey = i.first;
			}
		}
	}
}

void am::MapEditorPalete::mappingPalete() {

	int key{};

	for (unsigned int i{ 1 }; i <= sheet_.getSheetDim().y; ++i) {

		for (unsigned int j{ 1 }; j <= sheet_.getSheetDim().x; ++j) {

			sheet_.cut(Vector2u(j, i));
			sheet_.setPosition(Vector2f(static_cast<float>((j - 1) * sheet_.getSizeOneSprite().x), static_cast<float>((i - 1) * sheet_.getSizeOneSprite().y)));
			sprites_.insert({ key, sheet_ });
			++key;
		}

	}
}

void am::MapEditorPalete::drawSheetPalete() {

	paleteWindow_.clear();

	for (const auto& i : sprites_)
		paleteWindow_.draw(i.second);

	paleteWindow_.display();
}

inline bool am::MapEditorPalete::isOpen() const {

	return paleteWindow_.isOpen();
}

inline bool am::MapEditorPalete::isClosed(Event& event) {

	return event.type == sf::Event::Closed;
}

inline bool am::MapEditorPalete::isEvent(Event& event) {

	return paleteWindow_.pollEvent(event);
}

void am::MapEditorPalete::close() {

	paleteWindow_.close();
}

/* MapEditor */

am::MapEditor::MapEditor() {

	window_.create();
	gui_.setWindow(window_);
}

void am::MapEditor::loadData(bool& succeed) {

	gui_.convertData(data_.numberSheet, data_.numberTiles, data_.name, data_.path, succeed); // Gathers the data entered in the GUI by the user
	gui_.clear();

	mapMatrix_.resize(data_.numberTiles.y, data_.numberTiles.x);

	palete_.loadPalete(data_.numberSheet, data_.path); // We can know load the palete with the appropriate sheet

	window_.close(); // We close the window, in order to resize it -> This prevent a scale of every textures

	window_.setSize(Vector2u(data_.numberTiles.x * palete_.getPaleteSprite().getSizeOneSprite().x,
							 data_.numberTiles.y * palete_.getPaleteSprite().getSizeOneSprite().y));

	window_.create(); // Then we recreate it

	mapping();
}

void am::MapEditor::handleInputs(InputManager& input, bool& succeed) {

	gui_.handleInputs(input, window_);
	palete_.handleClick(input, currentSprite_, currentKey_);

	if (input.clickLeft() && succeed) {

		Vector2u mouseIndex{ positionToIndex(InputManager::mousePosition(window_), palete_) }; // We convert the mouse position into index

		/* /!\ InputManager::mousePosition(window_) is built like (line,row)
			   while the index that changeTile(const Vector2u&) takes is built like (x,y) abscissa and ordinate => (row, line) */

		if (mouseIndex.x >= 1 && mouseIndex.x <= data_.numberTiles.y && mouseIndex.y >= 1 && mouseIndex.y <= data_.numberTiles.x)
			changeTile(Vector2u(mouseIndex));
	}

	/* Hide and show the palete */

	if (input.key(InputManager::Key::LShift) && palete_.isOpen())
		palete_.close();

	else if (input.key(InputManager::Key::LControl) && !palete_.isOpen())
		palete_.loadPalete(data_.numberSheet, data_.path);

	else if (input.key(InputManager::Key::LControl) && input.key(InputManager::Key::S)) {

		if(save(data_.name, data_.path, data_.numberSheet, data_.numberTiles, mapMatrix_))
			std::clog << std::endl << "Level saved in " << data_.name << ".txt" << std::endl;
	}
}

void am::MapEditor::load() {

	Event event{};
	InputManager input{ window_, event };

	bool succeed{ false };

	Text release{ "All Mighty Editor - Beta", 30, Vector2f(10,10), Color::Red };

	while (window_.isOpen() || palete_.isOpen()) {

		while (window_.isEvent(event) || palete_.isEvent(event)) {

			if (event.type == sf::Event::Closed)
				window_.close();

			if (palete_.isClosed(event))
				palete_.close();

			if (gui_.buttonState(input, window_))
				data_.buttonClicked = true;

			handleInputs(input, succeed);
		}

		/* This condition will be true only once */

		if (data_.buttonClicked && !succeed)
			loadData(succeed); // We load the data one time

		window_.clear();

		if (!data_.buttonClicked) { // We don't draw the GUI nor the title (release) if the editor has been loaded
			
			window_.draw(gui_);
			window_.draw(release);
		}

		drawMap(window_);

		window_.display();

		palete_.drawSheetPalete();
	}
}

void am::MapEditor::mapping() {

	SpriteSheet sheet{ palete_.getPaleteSprite() };

	for (std::size_t i{}; i < data_.numberTiles.y; ++i) {

		for (std::size_t j{}; j < data_.numberTiles.x; ++j) {

			sheet.cut(Vector2u(1, 1)); // Initially we put the first tile everywhere

			sheet.setPosition(Vector2f(static_cast<float>(j * sheet.getSizeOneSprite().x), static_cast<float>(i * sheet.getSizeOneSprite().y)));

			sprites_.push_back(sheet);

			mapMatrix_(i, j) = 0;
		}
	}
}

void am::MapEditor::changeTile(const Vector2u& index) {

	/* We use the same algorithm used in the TileMap class */

	SpriteSheet sheet{ palete_.getPaleteSprite() };

	unsigned int scaleX = currentKey_ % sheet.getSheetDim().x; // Prevent to go over the number of tiles on a single line
	unsigned int scaleY = static_cast<std::size_t>(currentKey_ / sheet.getSheetDim().x);

	sheet.cut(Vector2u(scaleX + 1, scaleY + 1));
	sheet.setPosition(Vector2f(sprites_[(index.x - 1) * data_.numberTiles.x + index.y - 1].getPosition().x, // std::vector at method allow to reach an element
							   sprites_[(index.x - 1) * data_.numberTiles.x + index.y - 1].getPosition().y));

	sprites_[(index.x - 1) * data_.numberTiles.x + index.y - 1] = sheet;
	mapMatrix_(index.x - 1, index.y - 1) = currentKey_; // The matrix representing the map is modified too
}

inline am::Vector2u am::MapEditor::positionToIndex(const Vector2f& position, const MapEditorPalete& palete) {

	return Vector2u(static_cast<std::size_t>(std::size_t(position.y / palete.getPaleteSprite().getSizeOneSprite().y) + 1),
					static_cast<std::size_t>(std::size_t(position.x / palete.getPaleteSprite().getSizeOneSprite().x) + 1));
}

bool const am::MapEditor::save(const std::string& fileName, const std::string& pathTexture, const Vector2u& numberTilesSheet, const Vector2u& numberTiles, const  Matrix<int>& mapMatrix) {

	std::string path{ fileName + ".txt" };

	std::ofstream file{ path };

	bool succeed{false};

	file << pathTexture << "\n\n" << numberTilesSheet.x << ' ' << numberTilesSheet.y << "\n\n" << numberTiles.x << ' ' << numberTiles.y << "\n\n";

	if (file) {

		succeed = true;

		for (std::size_t i{}; i < numberTiles.y; ++i) {

			for (std::size_t j{}; j < numberTiles.x; ++j) {

				file << mapMatrix(i, j) << ' ';
			}

			file << '\n';
		}
	}

	else
		std::cerr << "Fail opening file" << std::endl;

	return succeed;
}

void am::MapEditor::drawMap(Window& window) {

	for (auto& i : sprites_)
		window.draw(i);
}