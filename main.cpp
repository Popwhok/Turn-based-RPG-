#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
#include <vector>
#include <chrono>
#include <thread>
using namespace std;
void StartAgain();
enum Class
{
	Robber = 1,
	Warrior,
	Vandal
};
class Player // Класс игрока
{
public:
	Player()
	{
		strength = rand() % 3 + 1;
		agility = rand() % 3 + 1;
		stamina = rand() % 3 + 1;
		hp = strength;
		weapon = "none";
		SneakAttack = Poison = ImpulseToAction = Shield = Fury = StoneSkin = false;
	}
	int GetStrength()
	{
		return strength;
	}
	void SetStrength(int strength)
	{
		this->strength = strength;
	}
	int GetAgility()
	{
		return agility;
	}
	void SetAgility(int agility)
	{
		this->agility = agility;
	}
	int GetStamina()
	{
		return stamina;
	}
	void SetStamina(int stamina)
	{
		this->stamina = stamina;
	}
	int GetHp()
	{
		return hp;
	}
	void SetHp(int hp)
	{
		this->hp = hp;
	}
	string GetWeapon()
	{
		return weapon;
	}
	void SetWeapon(string weapon)
	{
		this->weapon = weapon;
	}
	bool GetSnakeAttack()
	{
		return SneakAttack;
	}
	void SetSnakeAttack(bool SnakeAttack)
	{
		this->SneakAttack = SnakeAttack;
	}
	bool GetPoison()
	{
		return Poison;
	}
	void SetPoison(bool Poison)
	{
		this->Poison = Poison;
	}
	bool GetImpulseToAction()
	{
		return ImpulseToAction;
	}
	void SetImpulseToAction(bool ImpulseToAction)
	{
		this->ImpulseToAction = ImpulseToAction;
	}
	bool GetShield()
	{
		return Shield;
	}
	void SetShield(bool Shield)
	{
		this->Shield = Shield;
	}
	bool GetFury()
	{
		return Fury;
	}
	void SetFury(bool Fury)
	{
		this->Fury = Fury;
	}
	bool GetStoneSkin()
	{
		return StoneSkin;
	}
	void SetStoneSkin(bool StoneSkin)
	{
		this->StoneSkin = StoneSkin;
	}
private:
	int strength, agility, stamina, hp;
	string weapon;
	bool SneakAttack, Poison, ImpulseToAction, Shield, Fury, StoneSkin;
};
class Enemy // Класс противника
{
public:

	Enemy(string name, int strength, int agility, int stamina, int hp, string weapon)
	{
		this->name = name;
		this->strength = strength;
		this->agility = agility;
		this->stamina = stamina;
		this->hp = hp;
		this->weapon = weapon;
	}
	string GetName()
	{
		return name;
	}

	int GetStrength()
	{
		return strength;
	}
	void SetStrength(int strength)
	{
		this->strength = strength;
	}
	int GetAgility()
	{
		return agility;
	}
	void SetAgility(int agility)
	{
		this->agility = agility;
	}
	int GetStamina()
	{
		return stamina;
	}
	void SetStamina(int stamina)
	{
		this->stamina = stamina;
	}
	int GetHp()
	{
		return hp;
	}
	void SetHp(int hp)
	{
		this->hp = hp;
	}
	string GetWeapon()
	{
		return weapon;
	}
private:
	int strength, agility, stamina, hp;
	string name, weapon;
};
class GameLogic // Основная логика игра
{
public:
	void ClassLevel(Player& First, int c) // Распределение класса
	{
		if (c == Class::Robber)
		{
			First.SetHp(First.GetHp() + 4);
			lvlR += 1;
			SumLevel++;
			if (lvlR == 1)
			{
				First.SetSnakeAttack(true);
			}
			else if (lvlR == 2)
			{
				First.SetStrength(First.GetStrength() + 1);
			}
			else if (lvlR == 3)
			{
				First.SetPoison(true);
			}
		}
		else if (c == Class::Warrior)
		{
			First.SetHp(First.GetHp() + 5);
			lvlW += 1;
			SumLevel++;
			if (lvlW == 1)
			{
				First.SetImpulseToAction(true);
			}
			else if (lvlW == 2)
			{
				First.SetShield(true);
			}
			else if (lvlW == 3)
			{
				First.SetStrength(First.GetStrength() + 1);
			}
		}
		else if (c == Class::Vandal)
		{
			First.SetHp(First.GetHp() + 6);
			lvlV += 1;
			SumLevel++;
			if (lvlV == 1)
			{
				First.SetFury(true);
			}
			else if (lvlV == 2)
			{
				First.SetStoneSkin(true);
			}
			else if (lvlV == 3)
			{
				First.SetStamina(First.GetStamina() + 1);
			}
		}
	}
	Enemy RandomEnemy()
	{
		vector<Enemy> enemies = {
	   Enemy("Goblin", 1, 1, 1, 6, "Dagger"),
	   Enemy("Skeleton", 2, 2, 1, 11, "Cudgel"),
	   Enemy("Slime", 3, 1, 2, 10, "Lance"),
	   Enemy("Ghost", 1, 3, 1, 7, "Sword"),
	   Enemy("Golem", 3, 1, 3, 13, "Axe"),
	   Enemy("Dragon", 3, 3, 3, 23, "LegendarySword")
		};
		randomIndex = rand() % enemies.size();
		Enemy randomEnemy = enemies[randomIndex];
		return randomEnemy;
	}
	void Fight(Player& First, Enemy& randomEnemy) // Логика боя
	{

		PlayerWin = false;
		EnemyWin = false;


		if (First.GetAgility() >= randomEnemy.GetAgility()) //Первым ходит песронаж
		{
			cout << "Вы ходите первым!" << endl;
			chanceCheck = rand() % (First.GetAgility() + randomEnemy.GetAgility()) + 1;
			for (size_t i = 0; i < 50; i++)
			{
				cout << Move << " ход" << endl;
				FightLogicForPlayer(First, randomEnemy);
				if (PlayerWin == true)
				{
					i = 51;
					cout << "Вы победили в бою!" << endl;
					First.SetHp(CurrentHP);
					PlayerWin = false;
					Move = 1;
					if (WinCounter == 5)
					{
						cout << "Вы победили в игре!" << endl;
						StartAgain();
						return;

					}
					else
					{
						if (SumLevel < 3)
						{

							cout << "=== УЛУЧШЕНИЕ КЛАССА ===" << endl;
							cout << "1) + 1 к уровню разбойника" << endl;
							cout << "2) + 1 к уровню воина" << endl;
							cout << "3) + 1 к уровню варвара" << endl;
							cin >> c;
							this_thread::sleep_for(chrono::milliseconds(1500));
							system("cls");
							ClassLevel(First, c);
							randomEnemy = RandomEnemy();
							Fight(First, randomEnemy);
						}
						else
						{
							cout << "У вас максимальный уровень персонажа!" << endl;
							randomEnemy = RandomEnemy();
							Fight(First, randomEnemy);
						}

					}
				}
				else if (EnemyWin == true)
				{
					i = 51;
					cout << "Вы проиграли!" << endl;
					StartAgain();
					return;


				}
				else
				{
					cout << Move << " ход" << endl;
					FightLogicForEnemy(First, randomEnemy);
				}
			}
		}

		else // Первым ходит враг
		{
			cout << "Враг ходит первым!" << endl;
			chanceCheck = rand() % (First.GetAgility() + randomEnemy.GetAgility()) + 1;
			for (size_t i = 0; i < 50; i++)
			{
				cout << Move << " ход" << endl;
				FightLogicForEnemy(First, randomEnemy);
				if (PlayerWin == true)
				{
					i = 51;
					cout << "Вы победили в бою!" << endl;
					First.SetHp(CurrentHP);
					PlayerWin = false;
					Move = 1;
					if (WinCounter == 5)
					{
						cout << "Вы победили в игре!" << endl;
						StartAgain();
						return;

					}
					else
					{
						if (SumLevel < 3)
						{

							cout << "=== УЛУЧШЕНИЕ КЛАССА ===" << endl;
							cout << "1) + 1 к уровню разбойника" << endl;
							cout << "2) + 1 к уровню воина" << endl;
							cout << "3) + 1 к уровню варвара" << endl;
							cin >> c;
							this_thread::sleep_for(chrono::milliseconds(1500));
							system("cls");
							ClassLevel(First, c);
							randomEnemy = RandomEnemy();
							Fight(First, randomEnemy);
						}
						else
						{
							cout << "У вас максимальный уровень персонажа!" << endl;
							randomEnemy = RandomEnemy();
							Fight(First, randomEnemy);
						}

					}
				}
				else if (EnemyWin == true)
				{
					i = 51;
					cout << "Вы проиграли!" << endl;
					StartAgain();
					return;

				}
				else
				{
					cout << Move << " ход" << endl;
					FightLogicForPlayer(First, randomEnemy);
				}
			}
		}
		this_thread::sleep_for(chrono::milliseconds(4000));
		system("cls");

	}
	void FightLogicForPlayer(Player& First, Enemy& randomEnemy) // Логика боя для героя
	{
		Move++;
		DamageWeapon = 0;
		chanceCheck = rand() % (First.GetAgility() + randomEnemy.GetAgility()) + 1;
		CurrentHP = First.GetHp();
		if (Move == 1)
		{
			cout << "Вы встретили " << randomEnemy.GetName() << endl;
		}
		else
		{
			cout << "Вы сражаетесь с " << randomEnemy.GetName() << endl;
		}

		if (chanceCheck > randomEnemy.GetAgility()) // Проверка попал ли персонаж
		{
			cout << "Вы попали по врагу!" << endl;
			DamageWeapon = CheckDamageWeapon(First) + First.GetStrength();
			//Проверка наличия бонусов персонажа за уровни//////////////
			if (First.GetSnakeAttack() == true)
			{
				if (First.GetAgility() > randomEnemy.GetAgility())
				{
					DamageWeapon += 1;
					cout << "Использована скрытая атака: +1 к урону" << endl;
				}
			}
			if (First.GetImpulseToAction() == true)
			{
				if (Move == 1)
				{
					DamageWeapon *= 2;
					cout << "Использован порыв к действию: Действует двойной урон" << endl;
				}
			}
			if (First.GetFury() == true)
			{
				if (Move <= 3)
				{
					DamageWeapon += 2;
					cout << "Использована ярость: +2 к урону первые 3 хода" << endl;
				}
				else
				{
					DamageWeapon -= 1;
					cout << "Эффект ярости прошел: -1 к урону" << endl;
				}
			}
			/////////////////////////////////////////////////////////////
			if (randomEnemy.GetName() == "Goblin")
			{
				randomEnemy.SetHp(randomEnemy.GetHp() - DamageWeapon);
				if (randomEnemy.GetHp() <= 0)
				{
					cout << "Вы наносите " << DamageWeapon << " урона!" << endl;
					cout << "Враг побежден!" << endl;
					DropWeapon(First, randomEnemy);
					PlayerWin = true;
					WinCounter++;
				}
				else
				{
					cout << "Вы нанесли " << DamageWeapon << " урона!" << endl;
					cout << "У врага осталось " << randomEnemy.GetHp() << " здоровья!" << endl;
				}
			}
			else if (randomEnemy.GetName() == "Skeleton")
			{
				if (First.GetWeapon() == "Cudgel")
				{
					DamageWeapon *= 2;
					randomEnemy.SetHp(randomEnemy.GetHp() - DamageWeapon);
					if (randomEnemy.GetHp() <= 0)
					{
						cout << "Вы наносите " << DamageWeapon << " урона!" << endl;
						cout << "Враг побежден!" << endl;
						DropWeapon(First, randomEnemy);
						PlayerWin = true;
						WinCounter++;
					}
					else
					{
						cout << "Вы нанесли " << DamageWeapon << " урона!" << endl;
						cout << "У врага осталось " << randomEnemy.GetHp() << " здоровья!" << endl;
					}
				}
				else
				{
					randomEnemy.SetHp(randomEnemy.GetHp() - DamageWeapon);
					if (randomEnemy.GetHp() <= 0)
					{
						cout << "Вы наносите " << DamageWeapon << " урона!" << endl;
						cout << "Враг побежден!" << endl;
						DropWeapon(First, randomEnemy);
						PlayerWin = true;
						WinCounter++;
					}
					else
					{
						cout << "Вы нанесли " << DamageWeapon << " урона!" << endl;
						cout << "У врага осталось " << randomEnemy.GetHp() << " здоровья!" << endl;
					}
				}
			}
			else if (randomEnemy.GetName() == "Slime")
			{
				if (First.GetWeapon() == "Sword" || First.GetWeapon() == "Axe" || First.GetWeapon() == "LegendarySword")
				{
					if (First.GetWeapon() == "Sword")
					{
						DamageWeapon -= 3;
						randomEnemy.SetHp(randomEnemy.GetHp() - DamageWeapon);
						if (randomEnemy.GetHp() <= 0)
						{
							cout << "Вы наносите " << DamageWeapon << " урона!" << endl;
							cout << "Враг побежден!" << endl;
							DropWeapon(First, randomEnemy);
							PlayerWin = true;
							WinCounter++;
							return;
						}
						else
						{
							cout << "Вы нанесли " << DamageWeapon << " урона!" << endl;
							cout << "У врага осталось " << randomEnemy.GetHp() << " здоровья!" << endl;
						}

					}
					else if (First.GetWeapon() == "Axe")
					{
						DamageWeapon -= 4;
						randomEnemy.SetHp(randomEnemy.GetHp() - DamageWeapon);
						if (randomEnemy.GetHp() <= 0)
						{
							cout << "Вы наносите " << DamageWeapon << " урона!" << endl;
							cout << "Враг побежден!" << endl;
							DropWeapon(First, randomEnemy);
							PlayerWin = true;
							WinCounter++;
						}
						else
						{
							cout << "Вы нанесли " << DamageWeapon << " урона!" << endl;
							cout << "У врага осталось " << randomEnemy.GetHp() << " здоровья!" << endl;
						}
					}
					else if (First.GetWeapon() == "LegendarySword")
					{
						DamageWeapon -= 10;
						randomEnemy.SetHp(randomEnemy.GetHp() - DamageWeapon);
						if (randomEnemy.GetHp() <= 0)
						{
							cout << "Вы наносите " << DamageWeapon << " урона!" << endl;
							cout << "Враг побежден!" << endl;
							DropWeapon(First, randomEnemy);
							PlayerWin = true;
							WinCounter++;
						}
						else
						{
							cout << "Вы нанесли " << DamageWeapon << " урона!" << endl;
							cout << "У врага осталось " << randomEnemy.GetHp() << " здоровья!" << endl;
						}
					}
				}
				else
				{
					randomEnemy.SetHp(randomEnemy.GetHp() - DamageWeapon);
					if (randomEnemy.GetHp() <= 0)
					{
						cout << "Вы наносите " << DamageWeapon << " урона!" << endl;
						cout << "Враг побежден!" << endl;
						DropWeapon(First, randomEnemy);
						PlayerWin = true;
						WinCounter++;
					}
					else
					{
						cout << "Вы нанесли " << DamageWeapon << " урона!" << endl;
						cout << "У врага осталось " << randomEnemy.GetHp() << " здоровья!" << endl;
					}
				}
			}
			else if (randomEnemy.GetName() == "Ghost")
			{
				randomEnemy.SetHp(randomEnemy.GetHp() - DamageWeapon);
				if (randomEnemy.GetHp() <= 0)
				{
					cout << "Вы наносите " << DamageWeapon << " урона!" << endl;
					cout << "Враг побежден!" << endl;
					DropWeapon(First, randomEnemy);
					PlayerWin = true;
					WinCounter++;
				}
				else
				{
					cout << "Вы нанесли " << DamageWeapon << " урона!" << endl;
					cout << "У врага осталось " << randomEnemy.GetHp() << " здоровья!" << endl;
				}
			}
			else if (randomEnemy.GetName() == "Golem")
			{
				DamageWeapon = DamageWeapon - randomEnemy.GetStamina();
				randomEnemy.SetHp(randomEnemy.GetHp() - DamageWeapon);
				if (randomEnemy.GetHp() <= 0)
				{
					cout << "Вы наносите " << DamageWeapon << " урона!" << endl;
					cout << "Враг побежден!" << endl;
					DropWeapon(First, randomEnemy);
					PlayerWin = true;
					WinCounter++;
				}
				else
				{
					cout << "Вы нанесли " << DamageWeapon << " урона!" << endl;
					cout << "У врага осталось " << randomEnemy.GetHp() << " здоровья!" << endl;
				}
			}
			else if (randomEnemy.GetName() == "Dragon")
			{
				randomEnemy.SetHp(randomEnemy.GetHp() - DamageWeapon);
				if (randomEnemy.GetHp() <= 0)
				{
					cout << "Вы наносите " << DamageWeapon << " урона!" << endl;
					cout << "Враг побежден!" << endl;
					DropWeapon(First, randomEnemy);
					PlayerWin = true;
					WinCounter++;
				}
				else
				{
					cout << "Вы нанесли " << DamageWeapon << " урона!" << endl;
					cout << "У врага осталось " << randomEnemy.GetHp() << " здоровья!" << endl;
				}
			}

		}
		else
		{
			cout << "Вы промахнулись атакой!" << endl;
			cout << "Теперь ходит враг" << endl;
		}
		this_thread::sleep_for(chrono::milliseconds(5000));
		system("cls");
	}
	void FightLogicForEnemy(Player& First, Enemy& randomEnemy) // Логика боя противника
	{

		Move++;
		DamageWeapon = 0;
		if (Move == 1)
		{
			cout << "Вы встретили " << randomEnemy.GetName() << endl;
		}
		else
		{
			cout << "Вы сражаетесь с " << randomEnemy.GetName() << endl;
		}
		chanceCheck = rand() % (First.GetAgility() + randomEnemy.GetAgility()) + 1;
		if (chanceCheck > First.GetAgility())
		{
			cout << "Враг попадает атакой" << endl;
			if (randomEnemy.GetName() == "Goblin")
			{
				DamageWeapon = 1 + 2;
			}
			else if (randomEnemy.GetName() == "Skeleton")
			{
				DamageWeapon = 2 + 2;
			}
			else if (randomEnemy.GetName() == "Slime")
			{
				DamageWeapon = 1 + 3;
			}
			else if (randomEnemy.GetName() == "Ghost")
			{
				if (randomEnemy.GetAgility() > First.GetAgility())
				{
					DamageWeapon = 3 + 1 + 1;
				}
				else
				{
					DamageWeapon = 3 + 1;
				}
			}
			else if (randomEnemy.GetName() == "Golem")
			{
				DamageWeapon = 1 + 3;
			}
			else if (randomEnemy.GetName() == "Dragon")
			{
				if (Move % 3 == 0)
				{
					DamageWeapon = 4 + 3 + 3;
				}
				else
				{
					DamageWeapon = 4 + 3;
				}
			}
			if (First.GetShield() == true)
			{
				if (randomEnemy.GetStrength() < First.GetStrength())
				{
					DamageWeapon -= 3;
				}
			}
			if (First.GetStoneSkin() == true)
			{
				DamageWeapon -= First.GetStamina();
			}
			First.SetHp(First.GetHp() - DamageWeapon);
			if (First.GetHp() <= 0)
			{
				EnemyWin = true;
				cout << "Враг наносит сокрушительный урон!" << endl;
				return;
			}
			else
			{
				cout << "Враг наносит " << DamageWeapon << " урона" << endl;
				cout << "У вас осталось " << First.GetHp() << " здоровья" << endl;
			}

		}
		else
		{
			cout << "Враг промахнулся!" << endl;
		}
		this_thread::sleep_for(chrono::milliseconds(6000));
		system("cls");
	}
	int CheckDamageWeapon(Player First) // Возращает урон для оружия персонажа
	{
		if (First.GetWeapon() == "Dagger")
		{
			return 2;
		}
		else if (First.GetWeapon() == "Sword")
		{
			return 3;
		}
		else if (First.GetWeapon() == "Cudgel")
		{
			return 3;
		}
		else if (First.GetWeapon() == "Lance")
		{
			return 3;
		}
		else if (First.GetWeapon() == "Axe")
		{
			return 4;
		}
		else if (First.GetWeapon() == "LegendarySword")
		{
			return 10;
		}
	}
	void DropWeapon(Player& First, Enemy randomEnemy) // Механика выпадения оружия
	{
		int currentChoice;
		this_thread::sleep_for(chrono::milliseconds(1000));
		system("cls");
		cout << "Вам выпал " << randomEnemy.GetWeapon() << "!" << endl
			<< "Заменить текущее оружие?" << endl
			<< "1)Да" << endl
			<< "2)Нет" << endl;
		cin >> currentChoice;
		if (currentChoice == 1)
		{
			system("cls");
			cout << " Оружие заменено на " << randomEnemy.GetWeapon() << endl;
			First.SetWeapon(randomEnemy.GetWeapon());
			this_thread::sleep_for(chrono::milliseconds(2000));
		}
		else
		{
			system("cls");
			cout << "Оружие осталось прежним" << endl;
			this_thread::sleep_for(chrono::milliseconds(2000));
		}
	}

private:
	int Move = 1;
	int lvlR = 0, lvlV = 0, lvlW = 0;
	int WinCounter = 0, SumLevel = 0;
	int chanceCheck, randomIndex, DamageWeapon, CurrentHP, c;
	bool PlayerWin, EnemyWin;

};
class GameMenu
{
public:
	void Menu() // Начальное меню
	{
		cout << "============ Подземелья и драконы ============" << endl
			<< "1. Начать игру." << endl
			<< "2. Выйти." << endl;

	}

	auto Class(Player& First) // Меню для выбора класса
	{
		system("cls");
		cout << "Выберите класс персонажа:" << endl
			<< "1)Разбойник" << endl
			<< "2)Воин" << endl
			<< "3)Варвар" << endl;
		std::cin >> number;
		switch (number)
		{
		case 1:
			system("cls");
			cout << "Начальное оружие - кинжал" << endl
				<< "Урон оружия = 2" << endl
				<< "Класс получает 4 здоровья за уровень" << endl
				<< " ========================================================" << endl
				<< "|Бонус на 1 уровне |Бонус на 2 уровне|Бонус на 3 уровне  |" << endl
				<< "|Скрытая атака:    |                 |Яд:                |" << endl
				<< "|+1 к урону если   |                 |Наносит            |" << endl
				<< "|ловкость персонажа| Ловкость +1     |дополнительные +1  |" << endl
				<< "|выше ловкости цели|                 |урона на втором    |" << endl
				<< "|                  |                 |ходу, +2 на третьем|" << endl
				<< "|                  |                 |и так далее        |" << endl
				<< " ========================================================" << endl;
			cout << "Играть эти классом?" << endl
				<< "1)Да" << endl
				<< "2)Назад" << endl;
			std::cin >> number2;
			if (number2 == 1)
			{
				First.SetWeapon("Dagger");
				system("cls");
				return 1;
			}
			else
				system("cls");
			return 0;
		case 2:
			system("cls");

			cout << "Начальное оружие - Меч" << endl
				<< "Урон оружия = 3" << endl
				<< "Класс получает 5 здоровья за уровень" << endl
				<< " ========================================================" << endl
				<< "|Бонус на 1 уровне   |Бонус на 2 уровне|Бонус на 3 уровне|" << endl
				<< "|Порыв к действию:   |Щит:             |                 |" << endl
				<< "|В первый ход наносит|-3 к получаемому |                 |" << endl
				<< "|двойной урон        |урону если сила  |    Сила +1      |" << endl
				<< "|оружием             |персонажа выше   |                 |" << endl
				<< "|                    |силы атакующего  |                 |" << endl
				<< " ========================================================" << endl;
			cout << "Играть эти классом?" << endl
				<< "1)Да" << endl
				<< "2)Назад" << endl;
			std::cin >> number2;
			if (number2 == 1)
			{
				First.SetWeapon("Sword");
				system("cls");
				return 2;
			}
			else if (number2 == 2)
			{
				system("cls");
				return 0;
			}
			else
			{
				
			}
				
		case 3:
			system("cls");
			cout << "Начальное оружие - дубина" << endl
				<< "Урон оружия = 3" << endl
				<< "Класс получает 6 здоровья за уровень" << endl
				<< " ==========================================================" << endl
				<< "|Бонус на 1 уровне     |Бонус на 2 уровне|Бонус на 3 уровне|" << endl
				<< "|Ярость:               |Каменная кожа:   |                 |" << endl
				<< "|+2 к урону в первые 3 |Получаемый урон  |                 |" << endl
				<< "|хода, потом -1 к урону|снижается на     |Выносливость +1  |" << endl
				<< "|выше ловкости цели    |значение         |                 |" << endl
				<< "|                      |выносливости     |                 |" << endl
				<< " ==========================================================" << endl;
			cout << "Играть эти классом?" << endl
				<< "1)Да" << endl
				<< "2)Назад" << endl;
			std::cin >> number2;
			if (number2 == 1)
			{
				First.SetWeapon("Cudgel");
				system("cls");
				return 3;
			}
			else
				system("cls");
			return 0;
		default:
			system("cls");
			cout << "Ошибка! Неверный ввод!" << endl;
			this_thread::sleep_for(chrono::milliseconds(1500));
			return Class(First);
		}
	}
	int GetClassChoice(Player& First)
	{
		while (true)
		{
			int choice = Class(First);
			if (choice != 0)
			{
				return choice;
			}
		}
	}

private:
	int number, number2;
};

int RunGame(int choice)
{
	if (choice == 1)
	{
		GameMenu menu;
		GameLogic Game;
		int c;
		Player First;
		c = menu.Class(First);
		Game.ClassLevel(First, c);
		Enemy randomEnemy = Game.RandomEnemy();
		Game.Fight(First, randomEnemy);
	}
	else
	{
		return 0;
	}
}
void StartAgain()
{
	int currentChoice;
	cout << "Начать заново?" << endl
		<< "1)Да" << endl
		<< "2)Нет" << endl;
	cin >> currentChoice;
	switch (currentChoice)
	{
	case 1:
		system("cls");

		RunGame(1);
	case 2:
		system("cls");

		RunGame(2);
	default:
		break;
	}
}

int main()
{
	srand(time(nullptr));

	int choice;
	setlocale(LC_ALL, "Russian");
	GameMenu StartMenu;
	StartMenu.Menu();
	std::cin >> choice;
	RunGame(choice);

}

