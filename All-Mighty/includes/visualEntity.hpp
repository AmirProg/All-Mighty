#ifndef VISUALENTITY_HPP_INCLUDED
#define VISUALENTITY_HPP_INCLUDED

/****************************************
*
* ~ Visual Entity class ~
*
* Everything that could be considered
* as a visual entity
*
****************************************/

namespace am {

    class VisualEntity {

    protected:
        VisualEntity() = default;
        VisualEntity(const VisualEntity&) = default;
        virtual ~VisualEntity() = default;
        VisualEntity& operator=(const VisualEntity&) = default;
        VisualEntity(VisualEntity&&) = delete;
        VisualEntity& operator=(VisualEntity&&) = delete;

    private:
        virtual void update() = 0;
    };
}

#endif // VISUALENTITY_HPP_INCLUDED
