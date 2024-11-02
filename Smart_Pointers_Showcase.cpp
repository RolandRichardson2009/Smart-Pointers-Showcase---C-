#include <iostream>//Required for cout statements
#include <memory>//this is required for using smart pointers

using namespace std;//This grants entire application to the standard library

////////////////////////////////////////////////////////////////////////////
//BEGIN CLASSES
////////////////////////////////////////////////////////////////////////////

//This is a base class that is never instantiated.
class GameStructure
{
public:
	virtual void Help() {}
};

//This is a base class that is never instantiated.
class Character : public GameStructure
{
private:
	int Health;//private variable for health
public:
	string Name;
	virtual void Help() {}//Empty Help Function
	virtual void Talk(string stuffToSay)//talk function taking 1 argument
	{
		cout << Name + ": " + stuffToSay << endl;
	}
	virtual void Talk(string name, string stuffToSay)//talk function taking 2 argument
	{
		cout << name + ": " + stuffToSay << endl;
	}

	virtual int attack()//attack function
	{
		return 10;
	}

	//get function to return private variable
	virtual int getHealth()
	{
		return Health;
	}

	//set function to set private variable
	virtual void setHealth(int healthVar)
	{
		if (healthVar <= 0)//check if character has died and set health to 0
		{
			Health = 0;
			cout << "Character has Expired..." << endl;
		}
		else //Update health
		{
			Health = healthVar;
		}
	}
};
//This class is for the enemys
class Ninja :public Character
{
public:
	//Constructor
	Ninja(string nameVar, int healthVar)
	{
		Name = nameVar;
		setHealth(healthVar);
		cout << "A new ninja has been summoned!!!\n";
	}
	Ninja()
	{
		setHealth(75);
		cout << "A new ninja has been summoned!!!\n";
	}
	~Ninja()
	{
		cout << Name << " the ninja has been wiped from existance!!!\n";
	}
	void Help()
	{
		cout << "Ninja's are really cool, can you can use them to throw stars!" << endl;
	}
	int attack()
	{
		return 25;
	}
	int ThrowStars()
	{
		cout << "I am throwing stars!" << endl;
		return attack();
	}
};
//This class is for the player
class Pirate :public Character
{
public:
	//Constructor
	Pirate(string nameVar, int healthVar)
	{
		Name = nameVar;
		setHealth(healthVar);
		cout << "A new pirate has been summoned!!!\n";
	}
	Pirate()
	{
		setHealth(100);
		cout << "A new pirate has been summoned!!!\n";
	}
	~Pirate()
	{
		cout << Name <<" the pirate has been wiped from existance!!!\n";
	}
	void Help()
	{
		cout << "Pirate's are really cool, can you can use them to swing swords!" << endl;
	}
	//Function for the pirate attack
	int attack()
	{
		return 25;
	}
	int UseSword()
	{
		cout << "I am Swooshing my Sword!" << endl;
		return attack();
	}
};

////////////////////////////////////////////////////////////////////////////
//END CLASSES
////////////////////////////////////////////////////////////////////////////

int main()
{
	//variables listed for later use
	int playerHealthVar = -1;
	int enemyHealthVar = -1;
	int* playerHealthVarPtr = &playerHealthVar;
	int* enemyHealthVarPtr = &enemyHealthVar;
	unique_ptr<Pirate> pirateUniquePtr(new Pirate);//Creates a Unique Pointer
	unique_ptr<Ninja> ninjaUniquePtr(new Ninja);//Creates a Unique Pointer

	cout << "Are you ready for an intense game about pirates and ninjas? Get ready for an intense battle!" << endl;
	system("pause");//system pause asking user to press any key to continue.

	char userInputVar = ' ';//Place this variable outside of main loop so it can be used as an exit condition for the loop
	//The reason we are using a char instead of an int is to 
	//prevent exceptions being thrown for the user entering 
	//something other than an int.

	do//Begin main game loop
	{
		system("cls");//clears console for a clean view to prepare for current section.

		//Display menu to user
		cout << "1. Create a character." << endl;
		cout << "2. Display your stats." << endl;
		cout << "3. Attack." << endl;
		cout << "4. Exit game." << endl;

		cin >> userInputVar;//Get User Input for menu
		string playerNameVar = " ";
		//Ninja* newEnemyAppearsVarPtr = new Ninja("Tina", 75);
		ninjaUniquePtr->Name = "Tina";
		switch (userInputVar)//Process user's choice and display respective menu.
		{
		case '1':
			cout << "Please enter your name:" << endl;

			cin >> playerNameVar;
			pirateUniquePtr->Name = playerNameVar;
			//playerVarPtr = new Pirate(playerNameVar, 100);
			pirateUniquePtr->Talk("Stand back you fool!!!");
			system("pause");
			break;//Break out of case and back to main game loop
		case '2':
			cout << pirateUniquePtr->getHealth() << endl;
			system("pause");
			break;//Break out of case and back to main game loop
		case '3':
			enemyHealthVar = ninjaUniquePtr->getHealth();

			do
			{
				system("cls");
				cout << "Player attacks Ninja: " << endl;
				ninjaUniquePtr->setHealth(enemyHealthVar -= pirateUniquePtr->UseSword());
				if (ninjaUniquePtr->getHealth() < 1)
				{
					break;
				}
				system("pause");
				cout << "Ninja attacks Player: " << endl;
				*playerHealthVarPtr = pirateUniquePtr->getHealth();
				pirateUniquePtr->setHealth(*playerHealthVarPtr -= ninjaUniquePtr->ThrowStars());
				if (pirateUniquePtr->getHealth() < 1)
				{
					break;
				}
				system("pause");
			} while (ninjaUniquePtr->getHealth() > 0 || pirateUniquePtr->getHealth() > 0);
			cout << "battle is finished." << endl;

			system("pause");
			break;//Break out of case and back to main game loop
		case '4':
			system("cls");//clears console for a clean view to prepare for current section.
			cout << "Thanks for playing Pirates vs Ninjas!" << endl;
			break;//Break out of case and back to main game loop
		default:
			system("cls");//clears console for a clean view to prepare for current section.
			cout << "That is not a valid choice. Please try again." << endl;
			system("pause");//system pause asking user to press any key to continue.
			break;//Break out of case and back to main game loop
		}
	} while (userInputVar != '4');//Exit game loop when user enters the character 4.
	return 0;

}