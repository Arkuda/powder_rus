/*
 * PROPRIETARY INFORMATION.  This software is proprietary to POWDER
 * Development, and is not to be reproduced, transmitted, or disclosed
 * in any way without written permission.
 *
 * Produced by:	Jeff Lait
 *
 *      	POWDER Development
 *
 * NAME:        victory.cpp ( POWDER Library, C++ )
 *
 * COMMENTS:
 *	This handles all the code triggered when you win.  Or when
 *	you die.  The latter is better tested :>
 */

#include "glbdef.h"
#include "gfxengine.h"
#include "creature.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "victory.h"
#include "msg.h"
#include "item.h"
#include "control.h"
#include "speed.h"
#include "hiscore.h"
#include "encyc_support.h"
#include "stylus.h"
#include "buf.h"
#include "localization.h"

// Avatar name...
char glbAvatarName[100];
int  glbGameStartFrame;
bool glbWizard;
bool glbHasAlreadyWon;
bool glbTutorial;
bool glbStressTest = false;
bool glbMapStats = false;
bool glbOpaqueTiles = false;
s8   glbGender = -1;

BUF
victory_formattime(int endtime, int *scale)
{
    int		sec;
    int		min;
    int		hour;
    int		day;
    int		year;
    BUF		buf;

    // Count number of refreshes...
    endtime -= glbGameStartFrame;

    // Conver to seconds...
    endtime += 30;
    endtime /= 60;

    sec = endtime % 60;
    endtime /= 60;

    min = endtime % 60;
    endtime /= 60;

    hour = endtime % 24;
    endtime /= 24;
    day = endtime % 365;
    endtime /= 365;

    year = endtime;

    // Build the buffer...
    if (year)
    {
	if (scale)
	    *scale = 4;
	buf.sprintf("%d %s, %d %s, %d %s, %d %s и %d %s",
		year, ru_plural(year, "год", "года", "лет"),
		day, ru_plural(day, "день", "дня", "дней"),
		hour, ru_plural(hour, "час", "часа", "часов"),
		min, ru_plural(min, "минута", "минуты", "минут"),
		sec, ru_plural(sec, "секунда", "секунды", "секунд"));
    }
    else if (day)
    {
	if (scale)
	    *scale = 3;
	buf.sprintf("%d %s и %dч %dм %dс",
		day, ru_plural(day, "день", "дня", "дней"),
		hour,
		min,
		sec);
    }
    else if (hour)
    {
	if (scale)
	    *scale = 2;
	buf.sprintf("%dч %dм %dс",
		hour,
		min,
		sec);
    }
    else if (min)
    {
	if (scale)
	    *scale = 1;
	buf.sprintf("%d %s и %d %s", min,
		ru_plural(min, "минута", "минуты", "минут"), sec,
		ru_plural(sec, "секунда", "секунды", "секунд"));
    }
    else
    {
	if (scale)
	    *scale = 0;
	buf.sprintf("%d %s", sec,
		ru_plural(sec, "секунда", "секунды", "секунд"));
    }
    return buf;
}

void
glbShowIntrinsic(MOB *mob)
{
    int		i, j;
    int		aorb;
    
    BUF		buf;
    const char *intrinsiclist[NUM_INTRINSICS+1];
	
    buf.sprintf("%s внутренние качества:", mob->getPossessive());
    buf = gram_capitalize(buf);
    gfx_printtext(0, 3, buf.buffer());
    
    j = 0;
    for (i = 0; i < NUM_INTRINSICS; i++)
    {
	if (mob->hasIntrinsic((INTRINSIC_NAMES) i))
	{
	    intrinsiclist[j++] = glb_intrinsicdefs[i].name;
	}
    }
    if (!j)
	intrinsiclist[j++] = "Без внутренних качеств";
    intrinsiclist[j++] = 0;

    if (!glbStressTest)
	gfx_selectmenu(5, 4, intrinsiclist, aorb);

    // And clear it...
    for (j = 3; j < 18; j++)
    {
	gfx_cleartextline(j);
    }
}

static int
mob_compare(const void *v1, const void *v2)
{
    MOB_NAMES	*m1 = (MOB_NAMES *) v1;
    MOB_NAMES	*m2 = (MOB_NAMES *) v2;

    // We want to sort most experienced mobs first.
    if (glb_mobdefs[*m1].explevel > glb_mobdefs[*m2].explevel)
	return -1;
    else if (glb_mobdefs[*m1].explevel < glb_mobdefs[*m2].explevel)
	return 1;

    // Now, sort by name...
    return stricmp(glb_mobdefs[*m1].name, glb_mobdefs[*m2].name);
}

void
victory_buildSortedKillList(MOB_NAMES *mobtypes, int *numtypes, int *totalkill)
{
    int			j;
    MOB_NAMES		mob;

    if (totalkill)
	*totalkill = 0;

    j = 0;
    FOREACH_MOB(mob)
    {
	if (glbKillCount[mob])
	{
	    if (mob != MOB_AVATAR)
	    {
		mobtypes[j++] = mob;
		if (totalkill)
		    *totalkill += glbKillCount[mob];
	    }
	    else
	    {
		// Maybe put something cocky here?
	    }
	}
    }

    qsort(mobtypes, j, sizeof(MOB_NAMES), mob_compare);

    if (numtypes)
	*numtypes = j;
}

void
glbShowKillCount()
{
    int			 i, j, k;
    MOB_NAMES		 mobtypes[NUM_MOBS];
    char 		*moblist[NUM_MOBS+1]; // room for null`
    int			 aorb;
    int			 totalkill;

    gfx_printtext(0, 3, "Побеждённые существа:");

    victory_buildSortedKillList(mobtypes, &j, &totalkill);
    
    // Create names.
    for (i = 0; i < j; i++)
    {
	k = mobtypes[i];
	// What was I drinking when I put this second check in here?
	// We already only list things with a non-zero kill count?
	// This might mean the polycontrol code is broken...
	if (glbKillCount[k])
	{
	    moblist[i] = gram_createcount(glb_mobdefs[k].name,
						 glbKillCount[k],
						 true).strdup();
	}
    }
    if (!j)
    {
	moblist[j++] = strdup("никто");
    }
    moblist[j++] = 0;

    // Output the total number
    {
	BUF		buf;

	// We want to put a comma at the thousand mark.
	// Anyone who gets to the million mark will overflow our
	// display space, so we'll laugh at them.
	// HAHAHAHAHAHAHA.
	// Okay, I'll have mercy on the poor fool and switch to k
	// notation.
	if (totalkill >= 1000000)
	{
	    buf.sprintf("%d,%03dк", (totalkill / 1000000),
			    ((totalkill / 1000) % 1000));
	}
	else if (totalkill >= 1000)
	{
	    buf.sprintf("%d,%03d", (totalkill / 1000), (totalkill % 1000));
	}
	else
	    buf.sprintf("%d", totalkill);
	
	gfx_printtext(22, 3, buf);
    }
    
    gfx_selectmenu(5, 4, (const char **) moblist, aorb);

    // Free the created list.
    for (i = 0; i < j; i++)
    {
	if (moblist[i])
	    free(moblist[i]);
    }

    // And clear it...
    for (j = 3; j < 18; j++)
    {
	gfx_cleartextline(j);
    }
}

void writeItemActionBar(ITEM *item, bool onlyexamine);
ACTION_NAMES getInventoryActionStrip(int button);

void
glbVictoryScreen(bool didwin, const ATTACK_DEF *attack, MOB *src, ITEM *weapon)
{
    // Two very different possibilities: The avatar died, or lived?
    BUF			 buf;
    const char		*prof; 
    MOB			*avatar;
    int			 h, m;
    int			 endtime;
    bool		 ischeater = false;

    h = 1;
    m = 0;

    endtime = gfx_getframecount();

    if (!glbAvatarName[0])
	strcpy(glbAvatarName, "Ленивый игрок");

    // Determine if we are a cheater.
    // Check for save scumming.
    if (!hiscore_isnewgame() && hiscore_savecount() > 2)
	ischeater = true;
    // Check for Wizard mode.
    if (glbWizard)
	ischeater = true;

    if (glbTutorial)
    {
	// Inform the player of the nature of death in roguelikes.
	encyc_viewentry("HELP", HELP_DEATH);
	return;
    }

    BUF			posavatar;

    // Force upper case as GBA players are lazy.
    // (Well, in defense, it used to be impossible to input upper case)
    glbAvatarName[0] = toupper(glbAvatarName[0]);
    posavatar = gram_makepossessive(glbAvatarName);

    // Determine the avatar's profession...
    if ((avatar = MOB::getAvatar()))
    {
	if (glbHasAlreadyWon)
	{
	    // However, there is some sadness as coming here implies
	    // you died.
	    avatar->formatAndReport("%R <return> from retirement ended tragically!");
	}

	h = avatar->getHitDie();
	m = avatar->getMagicDie();
	
	if (h + m < 2)
	{
	    prof = "новичок";
	}
	else if (h + m < 4)
	{
	    prof = "неофит";
	}	
	else if (h + m > 50)
	    prof = "сильный игрок";
	else if (h > m + 2)
	{
	    if (h + m < 6)
		prof = "боец";
	    else if (h + m < 10)
		prof = "воин";
	    else
		prof = "великий воин";
	}
	else if (m > h + 2)
	{
	    if (h + m < 6)
		prof = "маг";
	    else if (h + m < 10)
		prof = "волшебник";
	    else
		prof = "великий волшебник";
	}
	else
	{
	    // Balanced....
	    if (h + m < 6)
		prof = "авантюрист";
	    else if (h + m < 10)
		prof = "боевой маг";
	    else
		prof = "великий боевой маг";
	}
    }
    else
	prof = "ЧТО СЛУЧИЛОСЬ С АВАТАРОМ?";

    if (didwin)
    {
	// Congratulations are in order!
	msg_report("Банзай! Банзай! Банзай!");
	if (src == avatar)
	{
	    // You killed it in a manly fight.
	    buf.sprintf("Безл'буб был побеждён %s %s! Все на поверхности восхваляют храбрость %s!", 
			 prof, glbAvatarName, glbAvatarName);
	    msg_report(buf);
	}
	else
	{
	    // You won by some clever strategem...

	    // First, announce how Baezl'bub fell...
	    if (src)
	    {
		BUF name = src->getName(true, true, true, true);
		buf.sprintf("Безл'буб пал от %s!", name.buffer());
	    }
	    else
	    {
		if (weapon)
		{
		    BUF name = weapon->getName();
		    buf.sprintf("Безл'буб's cruel reign of terror has ended, felled by %s!", name.buffer());
		}
		else
		    buf.sprintf("Хотя многие истории распространились о том, как умер Безл'буб, его смерть - это факт, в котором никто не сомневается!");
	    }
	    msg_report(buf);

	    // Next, make sure you get the credit you deserve... :>
	    buf.sprintf("Все на поверхности знают кого благодарить - %s, известного как %s!", prof, glbAvatarName);

	    msg_report(buf);
	}
    }
    else
    {
	// You died.  Loser.  I mean that in a good way.

	// First, the death text from the attack, if any...
	if (attack && attack->deathtext[0])
	{
	    buf.sprintf("%s.", attack->deathtext);
	    msg_report(buf);
	}
	else if (src == avatar)
	{
	    // If you killed yourself, say so...
	    if (weapon)
	    {
		BUF name = weapon->getName();
		buf.sprintf("Вы совершили самоубийство с помощью %s.",
			name.buffer());
	    }
	    else
		buf.sprintf("Вы совершили самоубийство.");
	    msg_report(buf);
	}

	if (h + m == 1)
	{
	    // Newbie death...
	    switch (rand_choice(2))
	    {
		case 0:
		    buf.sprintf("%s был сражён в молодом возрасте.",
			    glbAvatarName);
		    break;
		case 1:
		    buf.sprintf("%s %s стал ещё одной статистикой.",
			    prof, glbAvatarName);
		    break;
	    }
	    msg_report(buf);
	    if (src == avatar)
		src = 0;

	    const char *formattxt = "Надеюсь, будущие авантюристы извлекут урок из печального примера %s, чтобы быть более осторожными при игре с %s.";

	    if (src)
	    {
		BUF		name;

		if (src->hasIntrinsic(INTRINSIC_UNIQUE))
		    name = src->getName(false, true, true, true);
		else
		    name = gram_makeplural(src->getName(false, true, true, true));
		buf.sprintf(formattxt,
			glbAvatarName,
			name.buffer());
	    }
	    else if (weapon)
	    {
		BUF		name;

		if (weapon->isArtifact())
		    name = weapon->getName(false);
		else
		    name = gram_makeplural(weapon->getName(false));

		buf.sprintf(formattxt,
			glbAvatarName,
			name.buffer());	
	    }
	    else
	    {
		// No known source of the death.
		buf.sprintf(formattxt,
			glbAvatarName,
			"самих себя"
			);
	    }
	    
	    msg_report(buf);
	}
	else if (h + m > 15)
	{
	    // A great has died!
	    buf.sprintf("Мужчины плачут, а женщины рыдают, когда весть о смерти %s %s достигает поверхности!",
		    prof, glbAvatarName);
	    msg_report(buf);
	    BUF		name;
	    if (src)
		name = src->getName(true, true, true, true);
	    else if (weapon)
		name = weapon->getName();
	    else 
		name.reference("самоуверенность");
	    buf.sprintf("Столько надежд разбито самым гнусным из %s, %s.",
		    src ? "существ" : "вещей",
		    name.buffer());
	    msg_report(buf);
	}
	else
	{
	    // A mundane has died.
	    if (src && src != avatar)
	    {
		const char		*difficulty, *likelyerror;

		if (h + m > src->getExpLevel() + 10)
		{
		    difficulty = "просто ";
		    likelyerror = "безрассудная самоуверенность";
		}
		else if (h + m > src->getExpLevel() + 5)
		{
		    difficulty = "низкий ";
		    likelyerror = "самоуверенность";
		}
		else if (h + m > src->getExpLevel() + 2)
		{
		    difficulty = "превзойдённый ";
		    likelyerror = "плохое планирование";
		}
		else if (h + m > src->getExpLevel() - 2)
		{
		    difficulty = 0;
		    likelyerror = "отвратительная удача";
		}
		else if (h + m > src->getExpLevel() - 5)
		{
		    difficulty = "более могущественный ";
		    likelyerror = "откусывание больше, чем можно прожевать";
		}
		else if (h + m > src->getExpLevel() - 10)
		{
		    difficulty = "гораздо более могущественный ";
		    likelyerror = "выбор драки с кем-то сильнее";
		}
		else
		{
		    // 10 levels upwards.
		    difficulty = "значительно более могущественный ";
		    likelyerror = "глупо недооценивать своих врагов";
		}
		
		// Killed by a creature...
		BUF		name = src->getName(false, true, true, true);
		buf.sprintf("Смерть %s %s от рук %s%s%s послужит напоминанием будущим %s об опасностях %s.",
			     prof, posavatar.buffer(),
			     gram_getarticle(difficulty ? difficulty
							: name.buffer()),
			     difficulty ? difficulty : "",
			     name.buffer(),
			     prof,
			     likelyerror);
		msg_report(buf);
	    }
	    else if (src)
	    {
		buf.sprintf("Почему %s считал, что жизнь не стоит того, чтобы жить? Мы никогда не узнаем.");
		msg_report(buf);
	    }
	    else if (weapon)
	    {
		BUF		name = gram_makeplural(weapon->getName(false));
		buf.sprintf("Смерть %s %s используется и по сей день, чтобы напоминать детям об опасностях игры с %s.",
			     prof, posavatar.buffer(),
			     name.buffer());
		msg_report(buf);
	    }
	    else
	    {
		buf.sprintf("Репутация %s %s запятнана недостойной смертью.", 
			prof, posavatar.buffer());
		msg_report(buf);
	    }
	}
    }

    // For the purpose of hiscores, out of retirement players can
    // enter again.
    if (glbHasAlreadyWon)
    {
	didwin = true;
    }

    // Report hiscore results.
    hiscore_addAndDisplayEntry(avatar, didwin, ischeater);

    // Show mob kills
    glbShowKillCount();

    // First, list intrinsics...
    glbShowIntrinsic(avatar);

    // Then give the current god situation.
    avatar->pietyReport();

    // Now, onto listing the avatar's equipment and what not!
    // First, the generic character dump.
    avatar->characterDump(true, didwin, true, endtime);

    // We always examine the equipment.  The time spent asking the
    // question is wasted as cancelling the examine is the same
    // number of keys!
    if (1)
    {
	ITEM		*id;
	int		 y, x;

	for (y = 0; y < MOBINV_HEIGHT; y++)
	    for (x = 0; x < MOBINV_WIDTH; x++)
	    {
		id = avatar->getItem(x, y);
#if 1
		if (id)
		    id->markIdentified();
#endif
	    }

	STYLUSLOCK	styluslock(REGION_BOTTOMBUTTON);
	
	// Let the user peruse their inventory...
	gfx_showinventory(avatar);

	while (1)
	{
	    int		 dx = 0, dy = 0, cx, cy, select;

	    if (!gfx_isnewframe())
		continue;
	    if (hamfake_forceQuit())
		break;

	    // Prep the action bar...
	    {
		ITEM		*item;
		gfx_getinvcursor(cx, cy);
		item = avatar->getItem(cx, cy);
		writeItemActionBar(item, true);
	    }

	    // Handle input from external UI.
	    {
		ACTION_NAMES		action;
		int			iact, ispell;

		hamfake_externalaction(iact, ispell);

		if (iact != ACTION_NONE)
		{
		    action = (ACTION_NAMES) iact;
		    if (action == ACTION_INVENTORY)
		    {
			// Done
			break;
		    }
		    else if (action == ACTION_EXAMINE)
		    {
			ITEM		*item;

			// count as an examine.
			gfx_setinvcursor(cx, cy, false);
			item = avatar->getItem(cx, cy);
			// We don't want to quit on a click off as it is
			// more likely in the stylus world.
			if (!item)
			    continue;

			item->viewDescription();
			gfx_showinventory(avatar);

			continue;
		    }
		}
	    }

	    // Check for a view request...
	    if (styluslock.getbottombutton(select))
	    {
		if (select >= 0)
		{
		    ACTION_NAMES		action;

		    action = getInventoryActionStrip(select);

		    if (action == ACTION_INVENTORY)
		    {
			// Done
			break;
		    }
		    else if (action == ACTION_EXAMINE)
		    {
			ITEM		*item;

			// count as an examine.
			gfx_setinvcursor(cx, cy, false);
			item = avatar->getItem(cx, cy);
			// We don't want to quit on a click off as it is
			// more likely in the stylus world.
			if (!item)
			    continue;

			item->viewDescription();
			gfx_showinventory(avatar);

			continue;
		    }
		}
	    }

	    if (ctrl_hit(BUTTON_SELECT) ||
		ctrl_hit(BUTTON_B))
		break;

	    if (ctrl_hit(BUTTON_A))
	    {
		// Examine the item...
		ITEM		*item;

		gfx_getinvcursor(cx, cy);
		item = avatar->getItem(cx, cy);
		if (!item)
		    break;

		item->viewDescription();
		gfx_showinventory(avatar);

		continue;
	    }

	    ctrl_getdir(dx, dy);

	    if (!dx && !dy)
	    {
		if (stylus_queryinventoryitem(cx, cy))
		{
		    gfx_setinvcursor(cx, cy, false);
		}

		// Consume any key in case an invalid key was hit
		hamfake_getKeyPress(false);
		continue;
	    }

	    // A direction key is hit, update the cursor pos.
	    gfx_getinvcursor(cx, cy);
	    cx += dx;
	    cy += dy;
	    gfx_setinvcursor(cx, cy, false);
	}

	gfx_hideinventory();
    }

    buf.sprintf("Вы сделали %d ходов.", speed_gettime());
    msg_report(buf);

    // Report the time.
    {
	BUF		timename;
	int		scale;

	timename = victory_formattime(endtime, &scale);

	// Build the buffer...
	if (scale == 4)
	{
	    buf.sprintf("Вы потратили %s. Это просто безумие.",
		    timename.buffer());
	}
	else if (scale == 3)
	{
	    buf.sprintf("Вы потратили %s. Это просто безумие.",
		    timename.buffer());
	}
	else if (scale == 2)
	{
	    if (didwin)
		buf.sprintf("Вам потребовалось %s, чтобы победить Безл'буба.",
			timename.buffer());
	    else
		buf.sprintf("Вы потратили %s. И всё равно не выиграли.",
			timename.buffer());
	}
	else if (scale == 1)
	{
	    buf.sprintf("Вы потратили %s. %s",
		    timename.buffer(),
		    didwin ?
			"Впечатляющее достижение!" :
			"Продолжайте играть, и вы победите Безл'буба!");
	}
	else
	{
	    buf.sprintf("Это было быстро - %s.",
		    timename.buffer());
	}
	msg_report(buf);
    }

    if (didwin)
    {
	msg_report("Опубликуйте свой успех на RGRM!");
	msg_awaitaccept();
    }
    else
    {
	msg_report("Удачи в следующей жизни!");
	msg_awaitaccept();
    }
}
