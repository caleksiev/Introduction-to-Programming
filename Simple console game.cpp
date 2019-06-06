/**
*
* Solution to homework task
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2017/2018
*
* @author Tsvetan Alexiev
* @idnumber 45297
* @task 1C
* @compiler VC
*
*/
#include<iostream>
#include<ctime>
int main() {
	char choose_upgrade='0';
	double free_token = 0;
	char new_game='0';

	int my_health = 100;
	unsigned int my_damage = 10;
	unsigned int my_armor = 25;
	unsigned int my_luck = 5;
	unsigned int my_potion = 5;
	int my_healt_after_upgread = 0;
	int my_damage_after_upgread = 0;

	int it_healt = 50;
	unsigned int it_damage = 5;
	unsigned int it_armor = 5;
	unsigned int it_luck = 0;
	int it_healt_after_killing = 0;
	int it_damage_after_upgread = 0;

	int reduce_damage_percent = my_armor / 2;
	int reduce_it_damage_my_armor = (reduce_damage_percent*it_damage) / 100;

	int reduce_it_damage_prosent = it_armor / 2;
	int reduce_my_damage_it_armor = (reduce_it_damage_prosent*my_damage) / 100;

	int my_proc_luck = my_luck / 2;
	int it_proc_luck = it_luck / 2;

	

	srand((int)time(0));

	for (int i = 1;;i++)
	{
		if (i >= 2)//We enter in this loop aftet fitst killing of the monster
		{
			if (my_health <= 0)
			{
				
				std::cout << "You lost the game!" << std::endl;
				std::cout << "You can play a new game!" << std::endl;
				std::cout << "Do you want a play a new game?" << std::endl;
				std::cin >> new_game;
				switch (new_game)
				{
				case 'Y':
					if (free_token >= 1)
					{
						//vru6ta  pokazatel kum na4alnite usloviq,i zapo4va nova igra
						std::cout << "You have " << free_token << " and can play a new game!" << std::endl;
						free_token -= 1;
						my_health = 100;
						my_damage = 10;
						my_armor = 25;
						my_luck = 5;
						my_potion = 5;
						it_healt = 50;
						it_damage = 5;
						it_armor = 5;
						it_luck = 0;

						it_healt_after_killing = 0;
						it_damage_after_upgread = 0;

						my_healt_after_upgread = 0;
						my_damage_after_upgread = 0;

						reduce_damage_percent = my_armor / 2;
						reduce_it_damage_my_armor = (reduce_damage_percent*it_damage) / 100;

						my_proc_luck = my_luck / 2;
						it_proc_luck = it_luck / 2;

						reduce_it_damage_prosent = it_armor / 2;
						reduce_my_damage_it_armor = (reduce_it_damage_prosent*my_damage) / 100;
						continue;
					}
					else if (free_token < 1)
					{
						std::cout << "Sorry you have to pay!" << std::endl;
						return 1;
				default:
					std::cout << "Wrong input!" << std::endl;
					continue;
					}
				case 'N':
					std::cout << "The game is over!" << std::endl;
					return 0;
				}
			}
			else if (it_healt <= 0)
			{
				my_health = 100+my_healt_after_upgread;
				my_damage = 10+my_damage_after_upgread;
				std::cout << "You killed the monster and win the game!" << std::endl;
				free_token += 0.2;
				std::cout << "You have earned 0.2 tokens!" << " Now you have " << free_token << std::endl;

				int rand_potion =rand()% 2;
				if (rand_potion == 0)
				{
					my_potion += 1;
					std::cout << "After killing the monster you found one potion and now have " << my_potion << " potions!" << std::endl;
				}
				else
				{
					;
				}
				std::cout << "After killing the mosnter you have earned 5 points!" << std::endl;
				std::cout << "Chose which of your indicators you want to upgrade:(uppercase-[H],[D],[L] or [A])" << std::endl;
				for (int i = 1; i <= 5; i++)
				{

					std::cin >> choose_upgrade;
					switch (choose_upgrade)
					{
					case 'H':
						my_healt_after_upgread += 1;
						std::cout << "You have upgrade your health and now is " << my_health+my_healt_after_upgread << " !" << std::endl;
						continue;
					case 'D':
						my_damage_after_upgread += 1;
						std::cout << "You have upgrade your damage and now is " << my_damage+my_damage_after_upgread << " !" << std::endl;
						continue;
					case 'A':
						my_armor += 1;
						std::cout << "You have upgrade your armor and now is " << my_armor << " !" << std::endl;
						continue;
					case 'L':
						my_luck += 1;
						std::cout << "You have upgrade your luck and now is " << my_luck << " !" << std::endl;
						continue;
					default:
						std::cout << "Wrong input!" << std::endl;
						i--;
						continue;
					}
				}
			}
			if (it_healt <= 0)
			{
				it_healt = 50;
				it_healt_after_killing += 2;
				it_healt += it_healt_after_killing;
				it_damage = 5;
				it_damage_after_upgread += 2;
				it_damage += it_damage_after_upgread;
				it_armor += 2;
				it_luck += 2;
				my_health += my_healt_after_upgread;
				my_damage += my_damage_after_upgread;
				reduce_damage_percent = my_armor / 2;
				reduce_it_damage_my_armor = (reduce_damage_percent*it_damage) / 100;
				my_proc_luck = my_luck / 2;
				it_proc_luck = it_luck / 2;
				reduce_it_damage_prosent = it_armor / 2;
				reduce_my_damage_it_armor = (reduce_it_damage_prosent*my_damage) / 100;
				std::cout << std::endl;
				std::cout << "ABOUT DAMAGE REDUCTION!" << std::endl;
				std::cout << std::endl;
				std::cout << "Thanks to your armor monster damage is reduce with " << reduce_it_damage_my_armor <<"!"<< std::endl;
				it_damage -= reduce_it_damage_my_armor;
				std::cout << "Thanks to monster armor your damage is reduce with " << reduce_my_damage_it_armor << "!" << std::endl;
				my_damage -= reduce_my_damage_it_armor;
				std::cout << std::endl;
			}
		}
	while  (my_health > 0 && it_healt > 0)//IN THIS LOOP IS THE MAIN BATTLE
		{
			char input;
			std::cout << "Enter for action(uppercase):[I]-Show your stats,[A]-Attack,[D]-Defend,[P]-Potion or [X]-Exit!" << std::endl;
			std::cin >> input;
			switch (input)
			{
			case 'I':
				std::cout << "You current indcators: " << std::endl;
				std::cout << "Health: " << my_health << std::endl;
				std::cout << "Damage: " << my_damage << std::endl;
				std::cout << "Armor: " << my_armor << std::endl;
				std::cout << "Luck: " << my_luck << std::endl;
				std::cout << "Potion: " << my_potion << std::endl;
				std::cout << std::endl;
				std::cout << "Monster current indcators: " << std::endl;
				std::cout << "Health: " << it_healt << std::endl;
				std::cout << "Damage: " << it_damage << std::endl;
				std::cout << "Armor: " << it_armor << std::endl;
				std::cout << "Luck: " << it_luck << std::endl;
				continue;
			case 'A':
			{
				int rand_luck = rand() % 100;
				if (rand_luck >= 0 && rand_luck <= my_proc_luck)
				{
					it_healt -= (my_damage)*2;
					std::cout << "Wow you have attack the monster and make a critical hit! The monster lose " << (my_damage) * 2 << " health!" << std::endl;
					if (it_healt <= 0) { std::cout << "The monster lost all of his life!" << std::endl; continue; }
				}
				else
				{
					it_healt -= my_damage;
					std::cout << "You have attack the monster and it lost " << my_damage << " health!" << std::endl;
					if (it_healt <= 0) { std::cout << "The monster lose all of his life!" << std::endl; continue; }
				}
				std::cout << "Now the monster have " << it_healt << " health!" << std::endl;
				my_damage = 10+my_damage_after_upgread;//restore damage if the monster make a sucsesful defend or reduce  my damage

				int random = rand() % 2;
				if (random == 0)
				{
					if (rand_luck >= 0 && rand_luck <= it_proc_luck)
					{
						my_health -= (it_damage) * 2;
						std::cout << "Wow the monster make critical hit and you lose " << (it_damage) * 2 << " health!" << std::endl;
						if (my_health <= 0) { std::cout << "You lost all of your life!" << std::endl; continue; }
					}
					else
					{
						my_health -= it_damage;
						std::cout << "The monster attack you and take you " << it_damage << "  health!" << std::endl;
						if (my_health <= 0) { std::cout << "You lost all of your life!" << std::endl; continue; }
					}
					std::cout << "Your health is now " << my_health << " !" << std::endl;
				}
				else
				{
					rand_luck = rand() % 100;
					std::cout << "The monster defend himself!" << std::endl;
					if (rand_luck >= 0 && rand_luck <= it_proc_luck)
					{

						std::cout << "Wow the monster have luck and in the next move  will not become any damage!" << std::endl;
						my_damage = 0;
					}
					else
					{
						std::cout << "The monster reduce your damage with 50 procent!" << std::endl;
						my_damage = (my_damage * 50) / 100;
					}
				}
			}	continue;
			case 'D':
			{
				my_damage = 10 + my_damage_after_upgread;
				int rand_luck1 = rand() % 100;
				if (rand_luck1 >= 0 && rand_luck1 <= my_proc_luck)
				{
					std::cout << "Wow you defend yourself and have luck to reduce all of monster damage in his next attack!" << std::endl;
					it_damage = 0;
				}
				else
				{
					std::cout << "You defend yourself and reduce the damage of monster with 50 present!" << std::endl;
					it_damage = (it_damage * 50) / 100;
				}

				int random1 = rand() % 2;
				if (random1 == 0)
				{
					if (rand_luck1 >= 0 && rand_luck1 <= it_proc_luck)
					{
						it_damage -= reduce_it_damage_my_armor;
						my_health -= (it_damage) * 2;
						std::cout << "Wow the monster become critical hit and you lost " << (it_damage) * 2 << " health!" << std::endl;
						it_damage = (it_damage * 50) / 100;
						if (my_health <= 0) { std::cout << "You lost all of your life" << std::endl; continue; }

					}
					else
					{
						my_health -= it_damage;
						std::cout << "The monster attacked you and taked you " << it_damage << "  health" << std::endl;
						it_damage = (it_damage * 50) / 100;

						if (my_health <= 0) { std::cout << "You lost all of your life" << std::endl; continue; }
					}
					std::cout << "Your health is now " << my_health << " !" << std::endl;
				}
				else
				{
					rand_luck1 = rand() % 100;
					std::cout << "The monster defend himself!" << std::endl;
					if (rand_luck1 >= 0 && rand_luck1 <= it_proc_luck)
					{

						std::cout << "Wow the monster has luck and in the next attack he will not become any damage!" << std::endl;
						my_damage = 0;
					}
					else
					{
						std::cout << "The monster reduce your damage with 50 procent!" << std::endl;
						my_damage = (my_damage * 50) / 100;
					}
				}
				it_damage = 5 + it_damage_after_upgread;//restore monster damage if you r make a sucsesful defend or reduce it damage
				continue;
			}
			case 'P':
				if (my_potion == 0)
				{
					std::cout << "You have no more potion!" << std::endl;
					continue;
				}
				my_potion -= 1;
				my_health = 100;
				my_health += my_healt_after_upgread;
				std::cout << "You drink a potion and restore your health to " << my_health <<" !"<< std::endl;
				continue;
			case 'X':
				std::cout << "You exit the game!" << std::endl;
				return 0;
			default:
				std::cout << "Wrong input!" << std::endl;
			}
		}
	}
	return 0;
}