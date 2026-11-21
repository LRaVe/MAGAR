//
// Created by plt on 11/13/26.
//

#include "state/CastAction.h"
#include "state/PlayablePawn.h"
#include "state/Sorcerer.h"
#include "state/Tile.h"
#include "state/GameState.h"
#include "state/Board.h"
#include "state/AttackDice.h"
#include "GameEngine/RuleEngine.h"
#include <memory>

namespace state
{
    CastAction::CastAction(PlayablePawn* caster, Spell* spell) : caster(caster), spell(spell)
    {

    }

    CastAction::~CastAction() = default;

    bool CastAction::isOnStarTile(GameState& state) const
    {
        if (!caster) return false;

        Position caster_pos = caster->get_position();

        std::shared_ptr<Tile> current_tile = state.get_board().get_tile_from(caster_pos);

        return current_tile && current_tile->is_star_tile();

    }

    int CastAction::countSuccesses(const std::vector<bool>& draw)
    {
        int count = 0;
        for (bool hit : draw)
        {
            if (hit)
            {
                count++;
            }
        }
        return count;
    }

    void CastAction::execute(GameState& state)
    {
        //Verifions si le caster est sur une StarTile et si un sort existe
        if (!isOnStarTile(state) || spell==nullptr){
            return; // conditions non remplies
        }

        //Déterminons le nombre de dés à lancer
        int nb_dice = spell->get_nb_of_dice(state);

        //Lancer de dés
        AttackDice dice;
        dice.roll(nb_dice);
        std::vector<bool> result = dice.get_draw();

        //On ne souhaite obtenir que des succès
        resolve_draw(result, state);
    }

    bool CastAction::resolve_draw(const std::vector<bool>& draw, GameState& state)
    {
        if (!spell) {
            return false;
        }

        const int nb_dice = spell->get_nb_of_dice(state);

        if (countSuccesses(draw) != nb_dice) {
            return false;
        }

        spell->execute(state);
        return true;
    }

    bool CastAction::validate(GameEngine::RuleEngine& rules, GameState& state){
    return false; // à implémenter plus tard, pour l'instant on ne valide pas les actions
}
}


