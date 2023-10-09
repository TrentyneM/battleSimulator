// C++ Battle Simulator
// Written By: Trentyne Morgan
// Version 1

#include <iostream>			// Standard C++ Input / Ouput
#include <vector>			// C++ Vectors Library
#include <ctime>			// C++ Time Library
#include <stdlib.h>			// C Standard Libary

// =================
/* Game Variables */
// =================

// We put the enemy names in a vector so we can reference them using an index.
// *below we use int currentEnemy for the index.
std::vector<std::string> enemyName = {"Goblin", "Ghost", "Skeleton", "Troll"};


// Player and enemy health meters
int playerHealth = 100;				
int enemyHealth = 100;				


// We are going to use two booleans for the player and enemy's guard status
bool playerGuard = false;
bool enemyGuard = false; 

   		
int playerInput = 0;				// This variable is for the player's input
int rngValue = 0;					// Used for RNG Decisions
int currentEnemy = 0;				// This is the index for enemyName so the enemy can be random using the rngValue
int enemyFlee = false;				// Did the enemy run away?


// ======================================================================================
/* This function can show all of the variables we declared earlier in case of problems */
// ======================================================================================
void showAllVariables(){
	
	std::cout << "\n\n";
	std::cout << "Player Health: " << std::to_string(playerHealth) << "\n";
	std::cout << "Enemy Health: " << std::to_string(enemyHealth) << "\n";
	std::cout << "Is Player Guarding?: " << std::to_string(playerGuard) << "\n";
	std::cout << "Is Enemy Guarding?: " << std::to_string(enemyGuard) << "\n";
	std::cout << "Player's Input: " << std::to_string(playerInput) << "\n";
	std::cout << "Last Random Generated Number: " << std::to_string(playerHealth) << "\n";
	std::cout << "Current Enemy Index: " << std::to_string(currentEnemy) << "\n";
	std::cout << "Enemy Running Away?: " << std::to_string(enemyFlee) << "\n\n";
	
	// *Make sure we return nothing for a void function
	return;
}


// =================================
/* Show Player and Enemy's Health */
// =================================
void showHealth(){
	
	// To make sure that the player and enemy's health are not below 0
	// We check both when showHealth() is called.
	if (playerHealth < 0){
		
		playerHealth = 0;
		
	} else if (enemyHealth < 0){
	
		enemyHealth = 0;
	}
	
	//  Display both health meters
	std::cout << "\nPlayer Health: " << std::to_string(playerHealth) << "\n";
	std::cout << "Enemy Health: " << std::to_string(enemyHealth) << "\n";
	
	// Exit
	return;
}


// ================================
/* Function for the Enemy's turn */
// ================================
void enemyTurn(){
	
	// The enemy currently has 3 choices...
	
	// 1. Attack
	// 2. Guard
	// 3. Flee
	
	// Seed the random number generator here
	srand(time(NULL));
	
	// Generate a random number between 1 - 3
	rngValue = rand() % 3;
	
	// Store the enemy's choice in a new variable
	int enemyChoice = rngValue;
	
	// Reset rngValue for next use so the enemy doesn't make the same choice
	rngValue = 0;
	
	
	/* ---If the enemy's RNG picks attack.--- */
	if (enemyChoice == 1){
		
		
		// BUT... If the player is guarding
		if (playerGuard == true){
					
					
			// Our normalDamage amount is 20, so we create a new variable 
			// called reducedDamage that is random between 1 and 10	
			int reducedDamage = rand() % 10;
				
				
			// If the reducedDamage amount is greater than 0...
			if (reducedDamage > 0){
				
				// Display that the player is guarding
				std::cout << "\n\nPlayer is guarding.";
				
				// Display that the enemyname[at currentEnemy] attacked and the damage dealt
				// We use std::to_string() to convert the integer to a string.
				std::cout << " The " << enemyName[currentEnemy] <<" attacked! "; 
				std::cout << std::to_string(reducedDamage) << " damage dealt!\n\n";
				
				// Subtract the player's health by the damage amount.
				playerHealth -= reducedDamage;
				
				// Stop player's guard status
				playerGuard = false;		
					
			// Otherwise, if the reducedDamage amount is 0, then they missed.
			} else if (reducedDamage == 0){
					
				std::cout << "\n\nPlayer is guarding." << " The " << enemyName[currentEnemy] << " attacked, but missed...\n\n";
				playerGuard = false;
			}
				
				
		// Otherwise, if the player isn't guarding...
		} else if (playerGuard == false) {
				
			// Our normal damage amount is random between 1 and 20
			int normalDamage = rand() % 20;
				
			// If the reducedDamage amount is greater than 0 it's a hit
			if (normalDamage > 0){
				
				std::cout << "\n\nThe " << enemyName[currentEnemy] <<" attacked! "; 
				std::cout << std::to_string(normalDamage) << " damage dealt!\n\n";
				playerHealth -= normalDamage;
							
			// Otherwise, enemy missed.	
			} else if (normalDamage == 0){
					
				std::cout << "\n\nThe " << enemyName[currentEnemy] << " attacked, but missed...\n\n";
			}
		}

		// Exit 
		return;



	/* ---If the enemy's RNG guards...--- */
	} else if(enemyChoice = 2){
		
		// Set guard status to true
		enemyGuard = true;
		
		// Display guard status and return to main()
		std::cout << "\n\nThe enemy is guarding.\n\n";
		return;
	
	
	/* == NOTE ==:  You might wanna fix this gobble mess below later for flee code | | | == */
	/*                                                                             V V V    */
	
	// If the enemy's RNG flees, and health is less than or equal to 30,
	} else if (enemyChoice = 3 || enemyHealth >= 30){
		
		// Generate a new RNG value between 1 and 12
		rngValue = rand() % 12;
		
		// If rngValue is less than or equal to 6,
		// Enemy flees.
		if (rngValue >= 6){
			
			std::cout << "\n\nThe " << enemyName[currentEnemy] << " fleed! You Win!\n\n";
			exit(1);
			
		// Else if it's greater than 6,
		// Enemy just guards.	
		} else if (rngValue <= 6){
			
			enemyGuard = true;
			std::cout << "\n\nThe enemy is guarding.\n\n";
			return;
		}
	}	
}

// =============================
/* Function for player's turn */
// =============================
void playerTurn(){
	
	// Reset RNG to 0
	rngValue = 0;
	
	// Allows our player to enter input in the loop below
	bool allowPlayerInput = false;	
	
	// Start input loop
	allowPlayerInput = true;
	
	// While allowPlayerInput is true,
	while (allowPlayerInput == true){
		
		
		/* Ask the player which option they would like to pick then
		store it in playerInput */
		std::cout << "\n\n1.) Slash | 2.) Guard | 3.) Exit\nEnter the number of your choice: ";
		std::cin >> playerInput;
		
		
		// Make sure the player didn't put in an invalid option...
		// If the player input is less than or equal to 0 or (||) playerInput is greater than 3, Invalid option.
		if (playerInput <= 0 || playerInput > 3){
			
			std::cout << "\n\nInvalid Choice. Please try again..\n\n";
			
			
			
		/* ---If player enters 'slash'...--- */
		} else if (playerInput == 1){
			
			
			// Check if the enemy is guarding, if so,
			if (enemyGuard == true){
				
				// Picking a number 0 - 10 for our reduced damage value
				int reducedDamage = rand() % 10;
				
				// If the reducedDamage amount is greater than 0...
				if (reducedDamage > 0){
					
					// Display the enemyname[at currentEnemy] we just attacked
					std::cout << "\n\n" << enemyName[currentEnemy] << " is guarding.";
					std::cout << " You attacked the " << enemyName[currentEnemy] << "! ";
					
					// Don't forget to use std::to_string() for integers when printing output with std::cout()
					std::cout << std::to_string(reducedDamage) << " damage dealt!\n\n";
					
					// Subtract from enemy's health the reducedDamage amount.
					enemyHealth -= reducedDamage;
					
					// Set the enemy's guard status to false before exiting
					enemyGuard = false;
					break;
	
				// If the reducedDamage amount is less than or equal to 0
				} else if (reducedDamage <= 0){
					
					// Display that the enemy is guarding
					std::cout << "\n\n" << enemyName[currentEnemy] << " is guarding.";
					
					// Display that they attacked the enemy
					std::cout << " You attacked the " << enemyName[currentEnemy] << "... ";
					std::cout << "annnd you missed.\n\n";
					enemyGuard = false;
					
					// Exit the loop
					break;
				}
				
				
			// Otherwise, if the enemy isn't currently guarding..
			} else if (enemyGuard == false) {
				
				// Our normal damage range is between 0 and 20
				int normalDamage = rand() % 20;
				
				// If the normal amount is greater than 0...
				if (normalDamage > 0){
					
					// Display that we attacked the enemy and the damage dealt
					std::cout << "\n\nYou attacked the " << enemyName[currentEnemy] << "! ";
					std::cout << std::to_string(normalDamage) << " damage dealt!\n\n";
					
					// Subtract normal damage amount from the enemyHealth then exit the loop
					enemyHealth -= normalDamage;
					break;
						
				} else if (normalDamage == 0){
					
					// If the damage range is 0, the player missed
					std::cout << "\n\nYou attacked the " << enemyName[currentEnemy] << "... ";
					std::cout << "annnd you missed.\n\n";
					break;
				}
			}

			// If the loop is broken, exit.
			return;
			
			
		/* ---If player enters 'guard', reduce damage on enemy turn--- */
		} else if (playerInput == 2){
		
			// Display and set the player's guard status, and exit
			playerGuard = true;
			std::cout << "\n\nYou are guarding.\n\n";
			return;
			
			
		/* ---If player enters 'exit', exit program--- */
		} else if (playerInput == 3){
			
			// Exit Program
			exit(1);
		
		// Otherwise, not a valid option
		} else {
			
			std::cout << "\n\nInvalid Choice. Please try again..\n\n";
		}
	}
}

// ==============================
/* Main Game Function and Loop */
// ==============================

int main(){

	// Seeding RNG (we don't want the same enemy every time)
	srand(time(0));
	
	// Make a new RNG value between 1 and the size of the enemyName vector
	int rngValue = rand() % enemyName.size();
	
	// Display the title screen and the current enemy that's appeared
	std::cout << "\n==== C++ Battle Simulator ====\n\n" << "A " << enemyName[rngValue] << " has approached you!\n\n";
	
	// Show Health
	showHealth();
	
	// Store the current enemy for later.
	currentEnemy = rngValue;
	
	// Reset the RNG Value
	rngValue = 0;
	
	// While the player's health is not equal (!=) to 0, 
	// and (&&) the enemyHealth is not equal to 0...
	while (playerHealth != 0 && enemyHealth != 0){
	
		// Let the player take the first turn
		playerTurn();
		
		// Enemy has their turn
		enemyTurn();
		
		// Show the health bar
		showHealth();
		
	}
	
	// If the Player's health is less than or equal to 0, print game over.
	if (playerHealth <= 0){
		
		std::cout << "\n\nGAME OVER.\n\n";
		
		// Exit using stdlib.h
		exit(1);
		
	// Otherwise, if the enemy was slain the player wins
	} else if (enemyHealth <= 0){
		
		std::cout << "\n\n" << enemyName[currentEnemy] << " was slain! You Win!";
	}
}


