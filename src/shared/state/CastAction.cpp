//
// Created by plt on 11/13/26.
//

#include "state/CastAction.h"
#include "state/PlayablePawn.h"
#include "state/Sorcerer.h"
#include "state/Tile.h"
#include "state/StarTile.h"
#include "state/GameState.h"
#include "state/Board.h"
#include "state/AttackDice.h"
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

        return dynamic_cast<StarTile*>(current_tile.get()) != nullptr;

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
        int nb_dice = spell->number_of_dice;

        //Lancer de dés
        AttackDice dice;
        dice.roll(nb_dice);
        std::vector<bool> result = dice.get_draw();

        //On ne souhaite obtenir que des succès
        bool is_total_success = (countSuccesses(result) == nb_dice);

        if (is_total_success)
        {
            spell->execute(state);
        }
    }
}

