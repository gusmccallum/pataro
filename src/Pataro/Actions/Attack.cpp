#include <Pataro/Actions/Attack.hpp>

#include <Pataro/Engine.hpp>
#include <Pataro/Entity.hpp>
#include <Pataro/Components/Attacker.hpp>
#include <Pataro/Components/Destructible.hpp>

using namespace pat::action;

AttackAction::AttackAction(pat::Entity* source, pat::Entity* target) :
    m_source(source), m_target(target)
{}

pat::ActionResult AttackAction::perform(pat::Engine* engine)
{
    if (pat::component::Attacker* a = m_source->attacker(); a != nullptr)
    {
        // attack only if the other can be attacked
        if (pat::component::Destructible* d = m_target->destructible(); d != nullptr)
        {
            TCODColor text_color = (m_source == engine->get_player()) ? TCODColor::red : TCODColor::lightGrey;
            float dmg = a->power() - d->defense();
            if (dmg > 0.f)
                engine->get_gui()->message(text_color, m_source->get_name(), " attacks ", m_target->get_name(), " for ", dmg, " hit points.");
            else
                engine->get_gui()->message(TCODColor::lightGrey, m_source->get_name(), " attacks ", m_target->get_name(), " but it has no effect!");

            d->take_damage(m_target, a->power(), engine);
            return pat::ActionResult::Success;
        }

        engine->get_gui()->message(TCODColor::lightGrey, m_source->get_name(), " attacks ", m_target->get_name(), " in vain");
        return pat::ActionResult::Fail;
    }

    return pat::ActionResult::Fail;
}