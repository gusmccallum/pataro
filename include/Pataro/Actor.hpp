#ifndef PATARO_ACTOR_HPP
#define PATARO_ACTOR_HPP

#include <libtcod.hpp>

namespace pat
{
    class Actor
    {
    public:
        /**
        * @brief Construct a new Actor object
        * 
        * @param x position on X axis
        * @param y position on Y axis
        * @param ch ascii code representing the character
        * @param color the color for the actor
        */
        Actor(int x, int y, int ch, const TCODColor& color);

        /**
        * @brief display the actor on screen
        * 
        */
        void render() const;

        inline int get_x() const
        {
            return m_x;
        }

        inline int get_y() const
        {
            return m_y;
        }

        /**
         * @brief Move the actor
         * 
         * @param dx 
         * @param dy 
         */
        void move(int dx, int dy);

    private:
        int m_x;
        int m_y;
        int m_ch;
        TCODColor m_color;
    };
}

#endif