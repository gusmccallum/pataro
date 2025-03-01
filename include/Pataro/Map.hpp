#ifndef PATARO_MAP_HPP
#define PATARO_MAP_HPP

#include <Pataro/Map/Level.hpp>
#include <cereal/cereal.hpp>
#include <cereal/archives/binary.hpp>
#include <cereal/archives/portable_binary.hpp>
#include <cereal/archives/xml.hpp>

#include <cereal/types/string.hpp>
#include <cereal/types/utility.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/complex.hpp>
#include <cereal/types/base_class.hpp>
#include <cereal/types/array.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/map.hpp>
#include <cereal/types/utility.hpp>
#include <cereal/types/bitset.hpp>
#include <cereal/types/polymorphic.hpp>
#include <vector>

namespace pat
{
    class Entity;
    class Engine;

    class Map
    {
    public:
        /**
         * @brief Construct a new Map object
         * 
         * @param width 
         * @param height 
         * @param depth number of levels to generate
         */
        Map(unsigned width, unsigned height, std::size_t depth);

        /**
         * @brief Check if a tile at (x, y) is a wall
         * 
         * @param x 
         * @param y 
         * @return true 
         * @return false 
         */
        bool is_wall(int x, int y) const;

        /**
         * @brief check if an entity can walk on a given tile
         * 
         * @param x 
         * @param y 
         * @return true 
         * @return false 
         */
        bool can_walk(int x, int y) const;

        /**
         * @brief Tries to get an entity at x, y
         * 
         * @param x 
         * @param y 
         * @return Entity* nullptr if no entity was found
         */
        Entity* get_entity(int x, int y) const;

        /**
         * @brief Returns the closest monster to a given entity in a given range
         * 
         * @param from 
         * @param range 
         * @return Entity* 
         */
        Entity* get_closest_monster(Entity* from, float range) const;

        /**
         * @brief Compute the player field of view
         * 
         * @param x player position
         * @param y player position
         * @param fov_radius in tiles
         */
        void compute_fov(int x, int y, int fov_radius);

        /**
         * @brief Check if a tile is in the field of view
         * 
         * @param x 
         * @param y 
         * @return true 
         * @return false 
         */
        bool is_in_fov(int x, int y);

        /**
         * @brief Render the map on the screen
         * 
         * @param engine 
         */
        void render(Engine* engine);

        /**
         * @brief Update the current level
         * 
         * @param engine 
         */
        void update(Engine* engine);

        /**
         * @brief get the current level
         * 
         * @return const map::Level& 
         */
        inline map::Level& current_level() { return m_levels[m_current]; }

        template<class Archive>
        void save(Archive& archive)
        {
            archive(m_levels);
            archive(m_current);
        }

    private:
        std::vector<map::Level> m_levels;
        // TODO add method to change current level
        std::size_t m_current;
    };
}

#endif