#include <iostream>
#include <SFML/Graphics.hpp>

#include "Board.hpp"
#include "ActionLog.hpp"
#include "Vessel.hpp"

void vesselMenu(Board& board, int playerID);

int main(void) {
  Board board;
  vesselMenu(board, PLAYER1);
  return EXIT_SUCCESS;
}

void vesselMenu(Board& board, int playerID) {
    std::vector<int> coordinates(2);
    std::vector<ActionLog> logs = std::vector<ActionLog>(50);
    ActionLog log("");  // For upgrade and calculateDamage
    Vessel* vessel = nullptr;
    size_t upgradePoints = ELEMENT_COUNT*2; // Starting points
    bool exitMenu = false;

    while (!exitMenu) {
        std::cout << "\n--- Vessel Menu ---\n";
        std::cout << "1. Select Vessel (by Coordinates)\n";
        std::cout << "2. Insert Vessel\n";
        std::cout << "3. Upgrade Vessel\n";
        std::cout << "4. Calculate Damage\n";
        std::cout << "5. Show Action Logs\n";
        std::cout << "6. Exit\n";
        std::cout << "Choose an option: ";

        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::cout << "Enter coordinates (row and column): ";
                std::cin >> coordinates[0] >> coordinates[1];
                vessel = board.getVessel(coordinates, playerID);

                if (!vessel) {
                    std::cout << "Invalid coordinates or no vessel found.\n";
                } else {
                    std::cout << "Vessel selected at (" << coordinates[0] << ", " << coordinates[1] << ").\n";
                }
                break;
            }
            case 2: {
                std::cout << "Enter coordinates to insert vessel (row and column): ";
                std::cin >> coordinates[0] >> coordinates[1];

                std::cout << "Select Vessel Type:\n";
                std::cout << "0. HASHSET\n";
                std::cout << "1. REDBLACK\n";
                std::cout << "2. BINARYSEARCH\n";
                std::cout << "3. BTREE\n";
                std::cout << "4. SPLAYTREE\n";
                std::cout << "5. LINEARSEARCH\n";
                std::cout << "Enter vessel ID: ";

                int vesselID;
                std::cin >> vesselID;

                bool inserted = board.insertVessel(coordinates, vesselID, playerID, logs);
                if (inserted) {
                    std::cout << "Vessel inserted successfully!\n";
                } else {
                    std::cout << "Failed to insert vessel. Maybe invalid position?\n";
                }
                break;
            }
            case 3: {
                if (!vessel) {
                    std::cout << "No vessel selected. Please select a vessel first.\n";
                    break;
                }
                bool success = vessel->upgradeVessel(upgradePoints, logs);
                if (success) {
                    std::cout << "Vessel upgraded! Remaining upgrade points: " << upgradePoints << "\n";
                } else {
                    std::cout << "Upgrade failed. Not enough points or invalid operation.\n";
                }
                break;
            }
            case 4: {
                if (!vessel) {
                    std::cout << "No vessel selected. Please select a vessel first.\n";
                    break;
                }
                int damage = vessel->calculateDamage(log);
                std::cout << "Damage calculated: " << damage << "\n";
                break;
            }
            case 5: {
                std::cout << "\nAction Logs:\n";

                for (size_t i = 0; i < logs.size(); ++i) {
                    std::cout << "[" << i << "] " << logs[i].toString() << "\n";
                }
                std::cout << log.toString(); // Single log for upgrades/damages
                break;
            }
            case 6: {
                exitMenu = true;
                break;
            }
            default:
                std::cout << "Invalid option. Try again.\n";
        }
    }
}