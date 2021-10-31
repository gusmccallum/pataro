#ifndef PATARO_COMPONENTS_DESTRUCTIBLE_HPP
#define PATARO_COMPONENTS_DESTRUCTIBLE_HPP

#include <string>
#include <memory>

namespace pat
{
    class Entity;
    class Engine;
}

namespace pat::component
{
    class Destructible
    {
    public:
        /**
         * @brief Construct a new Destructible object
         * 
         * @param max_hp 
         * @param defense 
         * @param corpse_name the name of the Entity once dead
         */
        Destructible(float max_hp, float defense, const std::string& corpse_name);

        /**
         * @brief Destroy the Destructible object
         * 
         */
        virtual ~Destructible() = default;

        /**
         * @brief Handles damages given to the destructible
         * 
         * @param owner 
         * @param damage 
         * @param engine 
         * @return float the number of hit points actually taken
         */
        float take_damage(Entity* owner, float damage, Engine* engine);

        /**
         * @brief What happens when the owning entity dies is handled here
         * 
         * @param owner 
         * @param engine 
         */
        virtual void die(Entity* owner, Engine* engine);

        /**
         * @brief Heals damages
         * 
         * @param amount 
         * @return float 
         */
        float heal(float amount);

        inline bool  is_dead() { return m_hp <= 0.f; }
        inline float max_hp()  { return m_max_hp; }
        inline float hp()      { return m_hp; }
        inline float defense() { return m_defense; }

        inline std::unique_ptr<Destructible> clone() const { return std::unique_ptr<Destructible>(clone_impl()); }

        template<class Archive>
        void save(Archive& archive)
        {
            archive(m_max_hp, m_hp, m_defense, m_corpse_name);
        }

    protected:
        virtual Destructible* clone_impl() const;

    private:
        float m_max_hp, m_hp;
        float m_defense;
        std::string m_corpse_name;  ///< The Entity's name once dead
    };
}

#endif
