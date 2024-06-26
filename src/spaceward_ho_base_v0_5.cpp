#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include <cmath>
#include <random>
#include <chrono>
#include <fstream>
#include <sstream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

struct Planet {
    int x, y;
    int playerOwner;
    int population;
    double temperature;
    double gravity;
    double metal;
    std::unique_ptr<double[]> incomeGenerated;
    std::unique_ptr<double[]> devotedResources;
    std::unique_ptr<std::vector<int>> orbitalShips;
    std::unique_ptr<std::vector<int>> shipsInProduction;
    int terraformingLevel;
    int miningLevel;
    int shipbuildingCapacity;
    int defenseLevel;

    Planet(int x, int y, int playerOwner, int population, double temperature, double gravity, double metal)
        : x(x), y(y), playerOwner(playerOwner), population(population), temperature(temperature),
          gravity(gravity), metal(metal), terraformingLevel(0), miningLevel(0), shipbuildingCapacity(0), defenseLevel(0),
          incomeGenerated(std::make_unique<double[]>(5)),
          devotedResources(std::make_unique<double[]>(5)),
          orbitalShips(std::make_unique<std::vector<int>>()),
          shipsInProduction(std::make_unique<std::vector<int>>()) {}

    void updateIncome() {
        const double incomeFactor = 0.1;
        for (int i = 0; i < 5; ++i) {
            incomeGenerated[i] = population * devotedResources[i] * incomeFactor;
        }
    }

    void allocateResources(const std::unique_ptr<double[]>& allocation) {
        for (int i = 0; i < 5; ++i) {
            devotedResources[i] = allocation[i] * metal;
        }
    }

    void buildShip(int shipType) {
        if (metal >= 100 && shipbuildingCapacity > 0) {
            shipsInProduction->push_back(shipType);
            metal -= 100;
            --shipbuildingCapacity;
        }
    }

    void update(double deltaTime) {
        updatePopulationGrowth(deltaTime);
        updateResourceProduction(deltaTime);
        updateInfrastructure(deltaTime);
        updateDefense(deltaTime);
        applySpecialEffects(deltaTime);
    }

    void updatePopulationGrowth(double deltaTime) {
        double growthRate = calculateGrowthRate();
        double carryingCapacity = calculateCarryingCapacity();
        population += static_cast<int>(population * growthRate * (1 - population / carryingCapacity) * deltaTime);
    }

    void updateResourceProduction(double deltaTime) {
        double metalProduction = calculateMetalProduction();
        double energyProduction = calculateEnergyProduction();
        double foodProduction = calculateFoodProduction();
        metal += metalProduction * deltaTime;
        energy += energyProduction * deltaTime;
        food += foodProduction * deltaTime;
    }

    void updateInfrastructure(double deltaTime) {
        double infrastructureGrowth = calculateInfrastructureGrowth();
        infrastructure += infrastructureGrowth * deltaTime;
    }

    void updateDefense(double deltaTime) {
        double defenseGrowth = calculateDefenseGrowth();
        defense += defenseGrowth * deltaTime;
    }

    void applySpecialEffects(double deltaTime) {
        if (isVolcanicPlanet) {
            increaseMetalProduction(deltaTime);
            applyVolcanicActivityEffects(deltaTime);
        }
        if (isRadioactivePlanet) {
            increaseEnergyProduction(deltaTime);
            applyRadioactiveEffects(deltaTime);
        }
        if (isFertilePlanet) {
            increaseFoodProduction(deltaTime);
            applyFertileSoilEffects(deltaTime);
        }
    }

    // Placeholder functions for calculations and effects
    double calculateGrowthRate() { return 0.0; }
    double calculateCarryingCapacity() { return 0.0; }
    double calculateMetalProduction() { return 0.0; }
    double calculateEnergyProduction() { return 0.0; }
    double calculateFoodProduction() { return 0.0; }
    double calculateInfrastructureGrowth() { return 0.0; }
    double calculateDefenseGrowth() { return 0.0; }
    void increaseMetalProduction(double deltaTime) {}
    void applyVolcanicActivityEffects(double deltaTime) {}
    void increaseEnergyProduction(double deltaTime) {}
    void applyRadioactiveEffects(double deltaTime) {}
    void increaseFoodProduction(double deltaTime) {}
    void applyFertileSoilEffects(double deltaTime) {}

    bool isVolcanicPlanet = false;
    bool isRadioactivePlanet = false;
    bool isFertilePlanet = false;
    double energy = 0.0;
    double food = 0.0;
    double infrastructure = 0.0;
    double defense = 0.0;
};

struct Ship {
    int shipType;
    int attackPower;
    int defenseRating;
    int speed;
    int range;
    int miniaturizationLevel;

    Ship(int shipType, int attackPower, int defenseRating, int speed, int range, int miniaturizationLevel)
        : shipType(shipType), attackPower(attackPower), defenseRating(defenseRating),
          speed(speed), range(range), miniaturizationLevel(miniaturizationLevel) {}

    void upgrade(int attackBonus, int defenseBonus, int speedBonus, int rangeBonus) {
        attackPower += attackBonus;
        defenseRating += defenseBonus;
        speed += speedBonus;
        range += rangeBonus;
    }

    void applyMiniaturization(int level) {
        miniaturizationLevel = level;
    }

    void update(double deltaTime) {
        updateCombatReadiness(deltaTime);
        updateSensorRange(deltaTime);
        updateDetection(deltaTime);
        applySpecialAbilities(deltaTime);
    }

    void updateCombatReadiness(double deltaTime) {
        double suppliesEffect = calculateSuppliesEffect();
        double moraleEffect = calculateMoraleEffect();
        double conditionEffect = calculateConditionEffect();
        combatReadiness = baseCombatReadiness * suppliesEffect * moraleEffect * conditionEffect;
    }

    void updateSensorRange(double deltaTime) {
        double sensorUpgradeEffect = calculateSensorUpgradeEffect();
        sensorRange = baseSensorRange * sensorUpgradeEffect;
    }

    void updateDetection(double deltaTime) {
        std::vector<Ship*> nearbyShips = detectNearbyShips();
        std::vector<Planet*> nearbyPlanets = detectNearbyPlanets();
        updateTarget(nearbyShips, nearbyPlanets);
        engageInCombat(deltaTime);
    }

    void applySpecialAbilities(double deltaTime) {
        if (hasClockingAbility) {
            activateCloakingDevice(deltaTime);
        }
        if (hasTeleportationAbility) {
            teleportToRandomLocation(deltaTime);
        }
        if (hasRegenerationAbility) {
            regenerateHullAndShields(deltaTime);
        }
    }

    // Placeholder functions for calculations and effects
    double calculateSuppliesEffect() { return 0.0; }
    double calculateMoraleEffect() { return 0.0; }
    double calculateConditionEffect() { return 0.0; }
    double calculateSensorUpgradeEffect() { return 0.0; }
    std::vector<Ship*> detectNearbyShips() { return std::vector<Ship*>(); }
    std::vector<Planet*> detectNearbyPlanets() { return std::vector<Planet*>(); }
    void updateTarget(const std::vector<Ship*>& nearbyShips, const std::vector<Planet*>& nearbyPlanets) {}
    void engageInCombat(double deltaTime) {}
    void activateCloakingDevice(double deltaTime) {}
    void teleportToRandomLocation(double deltaTime) {}
    void regenerateHullAndShields(double deltaTime) {}

    double baseCombatReadiness = 0.0;
    double combatReadiness = 0.0;
    double baseSensorRange = 0.0;
    double sensorRange = 0.0;
    bool hasClockingAbility = false;
    bool hasTeleportationAbility = false;
    bool hasRegenerationAbility = false;
};

struct Technology {
    std::string name;
    int currentLevel;
    double costToUpgrade;
    std::unique_ptr<std::vector<double>> effects;

    Technology(const std::string& name, int currentLevel, double costToUpgrade)
        : name(name), currentLevel(currentLevel), costToUpgrade(costToUpgrade),
          effects(std::make_unique<std::vector<double>>()) {}

    void upgrade() {
        ++currentLevel;
        costToUpgrade *= 1.5;
    }

    void addEffect(double effect) {
        effects->push_back(effect);
    }

    double getEffect(int index) const {
        if (index >= 0 && index < effects->size()) {
            return effects->at(index);
        }
        return 0.0;
    }

    void update(double deltaTime) {
        updateResearchProgress(deltaTime);
        if (isResearched()) {
            applyEffects();
        }
    }

    void updateResearchProgress(double deltaTime) {
        double researchProgress = calculateResearchProgress(deltaTime);
        researchedPoints += researchProgress * deltaTime;
    }

    void applyEffects() {
        if (isMilitaryTechnology) {
            increaseShipCombatEffectiveness();
            unlockNewShipTypes();
        }
        if (isEconomyTechnology) {
            increaseResourceProductionEfficiency();
            unlockNewTradeRoutes();
        }
        if (isScienceTechnology) {
            increaseResearchSpeed();
            unlockNewTechnologies();
        }
    }

    // Placeholder functions for calculations and effects
    double calculateResearchProgress(double deltaTime) { return 0.0; }
    bool isResearched() { return false; }
    void increaseShipCombatEffectiveness() {}
    void unlockNewShipTypes() {}
    void increaseResourceProductionEfficiency() {}
    void unlockNewTradeRoutes() {}
    void increaseResearchSpeed() {}
    void unlockNewTechnologies() {}

    bool isMilitaryTechnology = false;
    bool isEconomyTechnology = false;
    bool isScienceTechnology = false;
    double researchedPoints = 0.0;
};

struct Player {
    int playerNumber;
    std::string playerName;
    double temperaturePreference;
    double gravityPreference;
    int totalPopulation;
    double totalFundsAccumulated;
    double totalFundsInBank;
    double totalGrossIncomePerTurn;
    double totalFundsSpentOnTechnology;
    std::unique_ptr<std::vector<int>> technologyLevels;
    std::unique_ptr<std::vector<int>> planetsOwned;
    std::unique_ptr<std::vector<int>> planetsSeen;
    std::unique_ptr<std::vector<int>> propertiesSeenInPossessionOfOtherPlayer;
    int numberOfShipsOwned;
    int researchPoints;
    std::unique_ptr<std::vector<int>> diplomacyStatus;

    Player(int playerNumber, const std::string& playerName, double temperaturePreference, double gravityPreference)
        : playerNumber(playerNumber), playerName(playerName), temperaturePreference(temperaturePreference),
          gravityPreference(gravityPreference), totalPopulation(0), totalFundsAccumulated(0.0),
          totalFundsInBank(0.0), totalGrossIncomePerTurn(0.0), totalFundsSpentOnTechnology(0.0),
          numberOfShipsOwned(0), researchPoints(0),
          technologyLevels(std::make_unique<std::vector<int>>()),
          planetsOwned(std::make_unique<std::vector<int>>()),
          planetsSeen(std::make_unique<std::vector<int>>()),
          propertiesSeenInPossessionOfOtherPlayer(std::make_unique<std::vector<int>>()),
          diplomacyStatus(std::make_unique<std::vector<int>>()) {}

    void updateTotalPopulation() {
        totalPopulation = 0;
        for (int planetId : *planetsOwned) {
            totalPopulation += gameGalaxy.getPlanet(planetId)->getPopulation();
        }
    }

    void updateTotalFunds() {
        totalFundsAccumulated += totalGrossIncomePerTurn;
        totalFundsInBank = totalFundsAccumulated - totalFundsSpentOnTechnology;
    }

    void updateGrossIncome() {
        totalGrossIncomePerTurn = 0.0;
        for (int planetId : *planetsOwned) {
            totalGrossIncomePerTurn += gameGalaxy.getPlanet(planetId)->getIncome();
        }
    }

    void investInTechnology(int technologyIndex, double funds) {
        if (funds <= totalFundsInBank) {
            totalFundsSpentOnTechnology += funds;
            totalFundsInBank -= funds;
            gameGalaxy.getTechnology(technologyIndex)->addResearchPoints(funds);
        }
    }

    void addPlanetOwned(int planetId) {
        planetsOwned->push_back(planetId);
    }

    void addPlanetSeen(int planetId) {
        planetsSeen->push_back(planetId);
    }

    void addPropertySeenInPossessionOfOtherPlayer(int propertyId) {
        propertiesSeenInPossessionOfOtherPlayer->push_back(propertyId);
    }

    void updateDiplomacyStatus(int playerNumber, int status) {
        if (playerNumber >= 0 && playerNumber < diplomacyStatus->size()) {
            diplomacyStatus->at(playerNumber) = status;
        }
    }

    void buildShip(int planetId, int shipType) {
        Planet* planet = gameGalaxy.getPlanet(planetId);
        if (planet != nullptr) {
            planet->buildShip(shipType);
            ++numberOfShipsOwned;
        }
    }

    void update(double deltaTime) {
        updateResourceGeneration(deltaTime);
        updateResearchProgress(deltaTime);
        updateShipProduction(deltaTime);
        updateShipMaintenance(deltaTime);
        updateDiplomacy(deltaTime);
        updateEspionage(deltaTime);
    }

    void updateResourceGeneration(double deltaTime) {
        double metalGeneration = calculateMetalGeneration(planetsOwned);
        double energyGeneration = calculateEnergyGeneration(planetsOwned);
        double foodGeneration = calculateFoodGeneration(planetsOwned);
    }

   void updateResearchProgress(double deltaTime) {
       for (int i = 0; i < technologies.size(); ++i) {
           double researchProgress = calculateResearchProgress(technologies[i], researchPoints[i], deltaTime);
           technologies[i].addResearchProgress(researchProgress);
           if (technologies[i].isResearched()) {
               applyTechnologyEffects(technologies[i]);
           }
       }
   }

   void updateShipProduction(double deltaTime) {
       for (int i = 0; i < planets.size(); ++i) {
           int shipProduction = calculateShipProduction(planets[i]);
           planets[i].addShipProductionProgress(shipProduction * deltaTime);
           while (planets[i].isShipCompleted()) {
               Ship newShip = createShip(planets[i].getCompletedShipType());
               ships.push_back(std::move(newShip));
               planets[i].removeCompletedShip();
           }
       }
   }

   void updateShipMaintenance(double deltaTime) {
       for (int i = 0; i < ships.size(); ++i) {
           double maintenanceCost = calculateShipMaintenanceCost(ships[i]);
           deductResources(maintenanceCost);
           applyShipMaintenanceEffects(ships[i], deltaTime);
       }
   }

   void updateDiplomacy(double deltaTime) {
       for (int i = 0; i < diplomacyStatus->size(); ++i) {
           updateDiplomacyStatus(i, deltaTime);
           applyDiplomacyEffects(i, deltaTime);
       }
   }

   void updateEspionage(double deltaTime) {
       for (int i = 0; i < espionageMissions.size(); ++i) {
           updateEspionageMissionProgress(espionageMissions[i], deltaTime);
           if (espionageMissions[i].isCompleted()) {
               applyEspionageMissionEffects(espionageMissions[i]);
               espionageMissions.erase(espionageMissions.begin() + i);
               --i;
           }
       }
   }

   // Placeholder functions for calculations and effects
   double calculateMetalGeneration(const std::unique_ptr<std::vector<int>>& planetsOwned) { return 0.0; }
   double calculateEnergyGeneration(const std::unique_ptr<std::vector<int>>& planetsOwned) { return 0.0; }
   double calculateFoodGeneration(const std::unique_ptr<std::vector<int>>& planetsOwned) { return 0.0; }
   double calculateResearchProgress(const Technology& technology, int researchPoints, double deltaTime) { return 0.0; }
   void applyTechnologyEffects(const Technology& technology) {}
   int calculateShipProduction(const Planet& planet) { return 0; }
   Ship createShip(int shipType) { return Ship(0, 0, 0, 0, 0, 0); }
   void deductResources(double cost) {}
   double calculateShipMaintenanceCost(const Ship& ship) { return 0.0; }
   void applyShipMaintenanceEffects(Ship& ship, double deltaTime) {}
   void updateDiplomacyStatus(int playerNumber, double deltaTime) {}
   void applyDiplomacyEffects(int playerNumber, double deltaTime) {}
   void updateEspionageMissionProgress(EspionageMission& mission, double deltaTime) {}
   void applyEspionageMissionEffects(const EspionageMission& mission) {}

   // Additional member variables
   std::vector<Technology> technologies;
   std::vector<int> researchPoints;
   std::vector<Planet> planets;
   std::vector<Ship> ships;
   std::vector<EspionageMission> espionageMissions;
   double metal = 0.0;
   double energy = 0.0;
   double food = 0.0;
};

struct GUIElement {
   int upperLeftX;
   int upperLeftY;
   int bottomRightX; 
   int bottomRightY;
};

class Galaxy {
public:
   Galaxy() {
       planets.reserve(100);
       players.reserve(10);
       initializeGameState();
   }

   void initializeGameState() {
       for (int i = 0; i < 100; ++i) {
           planets.emplace_back();
       }

       for (int i = 0; i < 10; ++i) {
           players.emplace_back();
       }
   }

   void updateGameState(double deltaTime) {
       for (auto& planet : planets) {
           planet.update(deltaTime);
       }

       for (auto& player : players) {
           player.update(deltaTime);
       }

       for (auto& ship : ships) {
           ship.update(deltaTime);
       }

       updateDiplomacy(deltaTime);
       updateTrade(deltaTime);
       updateResearch(deltaTime);
       updateCombat(deltaTime);
   }

   void handlePlayerInput() {
       while (window.pollEvent(event)) {
           if (event.type == sf::Event::MouseButtonPressed) {
               handleMouseClick(event.mouseButton);
           }

           if (event.type == sf::Event::KeyPressed) {
               handleKeyPress(event.key);
           }
       }
   }

   void renderGraphics() {
       renderGalaxy();
       renderPlanets();
       renderShips();
       renderPlayers();
       renderUI();
   }

private:
   std::vector<Planet> planets;
   std::vector<Player> players;
   std::vector<Ship> ships;
   std::vector<Technology> technologies;

   std::vector<int> turnsTaken;
   std::vector<double> initialValues;
   std::vector<std::unique_ptr<double>> populationGrowthCalculations;
   std::vector<int> windowSize;
   std::vector<GUIElement> guiElements;
   std::vector<int> assetSizes;
   std::vector<int> preloadedActions;
   std::vector<int> shipTypes;
   std::vector<int> statisticsGraphTabs;
   std::vector<int> playerActions;
   std::vector<double> allocationPercentages;
   std::vector<int> technologyNumbers;
   std::vector<std::unique_ptr<double>> technologyEffectEquations;
   std::vector<int> battleData;

   sf::RenderWindow window;
   sf::Event event;

   void handleMouseClick(const sf::Event::MouseButtonEvent& mouseButton) {}
   void handleKeyPress(const sf::Event::KeyEvent& key) {}

   void updateDiplomacy(double deltaTime) {}
   void updateTrade(double deltaTime) {}
   void updateResearch(double deltaTime) {}
   void updateCombat(double deltaTime) {}

   void renderGalaxy() {}
   void renderPlanets() {}
   void renderShips() {}
   void renderPlayers() {}
   void renderUI() {}
};

class GameUI {
public:
   GameUI(Galaxy& galaxy) : gameGalaxy(galaxy) {}

   void renderGalaxyView() {}
   void displayPlanetInfo(int planetId) {}
   void showShipOrbits(int planetId) {}
   void updateTechTreeUI() {}
   void updateMinimap() {}

   void displayShipInfo(int shipId) {
       Ship* ship = gameGalaxy.getShip(shipId);
       if (ship != nullptr) {
           std::cout << "Ship Type: " << ship->getShipType() << std::endl;
           std::cout << "Attack Power: " << ship->getAttackPower() << std::endl;
           std::cout << "Defense Rating: " << ship->getDefenseRating() << std::endl;
           std::cout << "Speed: " << ship->getSpeed() << std::endl;
           std::cout << "Range: " << ship->getRange() << std::endl;
           std::cout << "Miniaturization Level: " << ship->getMiniaturizationLevel() << std::endl;
       }
   }

   void displayTechnologyInfo(int techIndex) {
       Technology* tech = gameGalaxy.getTechnology(techIndex);
       if (tech != nullptr) {
           std::cout << "Technology Name: " << tech->getName() << std::endl;
           std::cout << "Current Level: " << tech->getCurrentLevel() << std::endl;
           std::cout << "Cost to Upgrade: " << tech->getCostToUpgrade() << std::endl;
           std::cout << "Effects:" << std::endl;
           for (int i = 0; i < tech->getNumEffects(); ++i) {
               std::cout << "  - Effect " << i+1 << ": " << tech->getEffect(i) << std::endl;
           }
       }
   }

   void displayPlayerInfo(int playerNumber) {
       Player* player = gameGalaxy.getPlayer(playerNumber);
       if (player != nullptr) {
           std::cout << "Player Name: " << player->getPlayerName() << std::endl;
           std::cout << "Temperature Preference: " << player->getTemperaturePreference() << std::endl;
           std::cout << "Gravity Preference: " << player->getGravityPreference() << std::endl;
           std::cout << "Total Population: " << player->getTotalPopulation() << std::endl;
           std::cout << "Total Funds: " << player->getTotalFunds() << std::endl;
           std::cout << "Technologies:" << std::endl;
           for (int i = 0; i < player->getNumTechnologies(); ++i) {
               std::cout << "  - " << player->getTechnologyName(i) << ": Level " << player->getTechnologyLevel(i) << std::endl;
           }
           std::cout << "Planets Owned:" << std::endl;
           for (int i = 0; i < player->getNumPlanetsOwned(); ++i) {
               std::cout << "  - Planet " << player->getPlanetOwned(i) << std::endl;
           }
       }
   }

private:
   Galaxy& gameGalaxy;
};

class GameLogic {
public:
   GameLogic(Galaxy& galaxy) : gameGalaxy(galaxy) {}

   void calculatePopulationGrowth() {}
   void allocateResources() {}
   void handleShipMovement() {}
   void resolveShipCombat() {}
   void researchTechnology() {}
   void applyTechnologyEffects() {}
   void makeAIDecisions() {}

   void terraformPlanet(int planetId, int targetTemp, double targetGravity) {
       Planet* planet = gameGalaxy.getPlanet(planetId);
       if (planet != nullptr) {
           double tempProgress = calculateTerraformingProgress(planet->getTemperature(), targetTemp);
           double gravityProgress = calculateTerraformingProgress(planet->getGravity(), targetGravity);
           planet->setTemperature(planet->getTemperature() + tempProgress);
           planet->setGravity(planet->getGravity() + gravityProgress);
           applyTerraformingEffects(planet);
       }
   }

   void conductMining(int planetId) {
       Planet* planet = gameGalaxy.getPlanet(planetId);
       if (planet != nullptr) {
           double miningYield = calculateMiningYield(planet->getMetal(), planet->getMiningLevel());
           planet->setMetal(planet->getMetal() - miningYield);
           applyMiningEffects(planet, miningYield);
       }
   }

   void performShipMaintenance(int playerId) {
       Player* player = gameGalaxy.getPlayer(playerId);
       if (player != nullptr) {
           for (int i = 0; i < player->getNumShipsOwned(); ++i) {
               int shipId = player->getShipOwned(i);
               Ship* ship = gameGalaxy.getShip(shipId);
               if (ship != nullptr) {
                   double maintenanceCost = calculateMaintenanceCost(ship);
                   player->deductFunds(maintenanceCost);
                   applyMaintenanceEffects(ship);
               }
           }
       }
   }

   void engageInDiplomacy(int playerId, int otherPlayerId) {
       Player* player = gameGalaxy.getPlayer(playerId);
       Player* otherPlayer = gameGalaxy.getPlayer(otherPlayerId);
       if (player != nullptr && otherPlayer != nullptr) {
           double diplomaticInfluence = calculateDiplomaticInfluence(player, otherPlayer);
           updateDiplomacyStatus(player, otherPlayer, diplomaticInfluence);
           applyDiplomacyEffects(player, otherPlayer);
       }
   }

   void colonizePlanet(Player& player, Planet& planet) {
       if (isPlanetSuitable(player, planet)) {
           establishColony(player, planet);
           planet.setPlayerOwner(player.getPlayerNumber());
           planet.setPopulation(initialColonyPopulation);
           applyColonizationEffects(player, planet);
       }
   }

   void developPlanet(Player& player, Planet& planet) {
       allocateDevelopmentResources(player, planet);
       updateInfrastructure(planet);
       updateProduction(planet);
       updateDefenses(planet);
       applyDevelopmentEffects(player, planet);
   }

   void conductEspionage(Player& player, Player& targetPlayer) {
       double successProbability = calculateEspionageSuccessProbability(player, targetPlayer);
       double randomValue = generateRandomValue();
       if (randomValue <= successProbability) {
           stealResources(player, targetPlayer);
           stealTechnologies(player, targetPlayer);
           stealInformation(player, targetPlayer);
       } else {
           applyEspionagePenalties(player, targetPlayer);
       }
   }

   void conductSabotage(Player& player, Player& targetPlayer) {
       double successProbability = calculateSabotageSuccessProbability(player, targetPlayer);
       double randomValue = generateRandomValue();
       if (randomValue <= successProbability) {
           damageInfrastructure(targetPlayer);
           damageProduction(targetPlayer);
           damageDefenses(targetPlayer);
       } else {
           applySabotagePenalties(player, targetPlayer);
       }
   }

private:
   Galaxy& gameGalaxy;

   // Placeholder functions for calculations and effects
   double calculateTerraformingProgress(double currentValue, double targetValue) { return 0.0; }
   void applyTerraformingEffects(Planet* planet) {}
   double calculateMiningYield(double metal, int miningLevel) { return 0.0; }
   void applyMiningEffects(Planet* planet, double miningYield) {}
   double calculateMaintenanceCost(Ship* ship) { return 0.0; }
   void applyMaintenanceEffects(Ship* ship) {}
   double calculateDiplomaticInfluence(Player* player, Player* otherPlayer) { return 0.0; }
   void updateDiplomacyStatus(Player* player, Player* otherPlayer, double diplomaticInfluence) {}
   void applyDiplomacyEffects(Player* player, Player* otherPlayer) {}
   bool isPlanetSuitable(const Player& player, const Planet& planet) { return true; }
   void establishColony(Player& player, Planet& planet) {}
   void applyColonizationEffects(Player& player, Planet& planet) {}
   void allocateDevelopmentResources(Player& player, Planet& planet) {}
   void updateInfrastructure(Planet& planet) {}
   void updateProduction(Planet& planet) {}
   void updateDefenses(Planet& planet) {}
   void applyDevelopmentEffects(Player& player, Planet& planet) {}
   double calculateEspionageSuccessProbability(const Player& player, const Player& targetPlayer) { return 0.0; }
   double generateRandomValue() { return 0.0; }
   void stealResources(Player& player, Player& targetPlayer) {}
   void stealTechnologies(Player& player, Player& targetPlayer) {}
   void stealInformation(Player& player, Player& targetPlayer) {}
   void applyEspionagePenalties(Player& player, Player& targetPlayer) {}
   double calculateSabotageSuccessProbability(const Player& player, const Player& targetPlayer) { return 0.0; }
   void damageInfrastructure(Player& targetPlayer) {}
   void damageProduction(Player& targetPlayer) {}
   void damageDefenses(Player& targetPlayer) {}
   void applySabotagePenalties(Player& player, Player& targetPlayer) {}

   int initialColonyPopulation = 0;
};

class SaveGame {
public:
   SaveGame(const Galaxy& galaxy) : gameGalaxy(galaxy) {}

   void saveGameState(const std::string& filename) {
       std::ofstream file(filename);
       if (file.is_open()) {
           file << gameGalaxy.getNumPlanets() << std::endl;
           for (int i = 0; i < gameGalaxy.getNumPlanets(); ++i) {
               Planet* planet = gameGalaxy.getPlanet(i);
               file << planet->getX() << " " << planet->getY() << " " << planet->getPlayerOwner() << " "
                    << planet->getPopulation() << " " << planet->getTemperature() << " " << planet->getGravity()
                    << " " << planet->getMetal() << " " << planet->getTerraformingLevel() << " "
                    << planet->getMiningLevel() << " " << planet->getShipbuildingCapacity() << " "
                    << planet->getDefenseLevel() << std::endl;
           }

           file << gameGalaxy.getNumPlayers() << std::endl;
           for (int i = 0; i < gameGalaxy.getNumPlayers(); ++i) {
               Player* player = gameGalaxy.getPlayer(i);
               file << player->getPlayerNumber() << " " << player->getPlayerName() << " "
                    << player->getTemperaturePreference() << " " << player->getGravityPreference() << " "
                    << player->getTotalPopulation() << " " << player->getTotalFunds() << " "
                    << player->getNumTechnologies() << " " << player->getNumPlanetsOwned() << " "
                    << player->getNumShipsOwned() << " " << player->getResearchPoints() << std::endl;
           }

           file << gameGalaxy.getNumShips() << std::endl;
           for (int i = 0; i < gameGalaxy.getNumShips(); ++i) {
               Ship* ship = gameGalaxy.getShip(i);
               file << ship->getShipType() << " " << ship->getAttackPower() << " " << ship->getDefenseRating()
                    << " " << ship->getSpeed() << " " << ship->getRange() << " " << ship->getMiniaturizationLevel()
                    << std::endl;
           }

           file << gameGalaxy.getNumTechnologies() << std::endl;
           for (int i = 0; i < gameGalaxy.getNumTechnologies(); ++i) {
               Technology* tech = gameGalaxy.getTechnology(i);
               file << tech->getName() << " " << tech->getCurrentLevel() << " " << tech->getCostToUpgrade()
                    << " " << tech->getNumEffects() << std::endl;
               for (int j = 0; j < tech->getNumEffects(); ++j) {
                   file << tech->getEffect(j) << " ";
               }
               file << std::endl;
           }

           file.close();
           std::cout << "Game state saved successfully!" << std::endl;
       } else {
           std::cout << "Unable to save game state. File could not be opened." << std::endl;
       }
   }

   void loadGameState(const std::string& filename) {
       std::ifstream file(filename);
       if (file.is_open()) {
           int numPlanets;
           file >> numPlanets;
           gameGalaxy.clearPlanets();
           for (int i = 0; i < numPlanets; ++i) {
               int x, y, playerOwner, population;
               double temperature, gravity, metal;
               int terraformingLevel, miningLevel, shipbuildingCapacity, defenseLevel;
               file >> x >> y >> playerOwner >> population >> temperature >> gravity >> metal
                    >> terraformingLevel >> miningLevel >> shipbuildingCapacity >> defenseLevel;
               gameGalaxy.addPlanet(new Planet(x, y, playerOwner, population, temperature, gravity, metal,
                                               terraformingLevel, miningLevel, shipbuildingCapacity, defenseLevel));
           }

           int numPlayers;
           file >> numPlayers;
           gameGalaxy.clearPlayers();
           for (int i = 0; i < numPlayers; ++i) {
               int playerNumber;
               std::string playerName;
               double temperaturePreference, gravityPreference;
               int totalPopulation, numTechnologies, numPlanetsOwned, numShipsOwned, researchPoints;
               double totalFunds;
               file >> playerNumber >> playerName >> temperaturePreference >> gravityPreference
                    >> totalPopulation >> totalFunds >> numTechnologies >> numPlanetsOwned
                    >> numShipsOwned >> researchPoints;
               gameGalaxy.addPlayer(new Player(playerNumber, playerName, temperaturePreference, gravityPreference,
                                               totalPopulation, totalFunds, numTechnologies, numPlanetsOwned,
                                               numShipsOwned, researchPoints));
           }

           int numShips;
           file >> numShips;
           gameGalaxy.clearShips();
           for (int i = 0; i < numShips; ++i) {
               int shipType, attackPower, defenseRating, speed, range, miniaturizationLevel;
               file >> shipType >> attackPower >> defenseRating >> speed >> range >> miniaturizationLevel;
               gameGalaxy.addShip(new Ship(shipType, attackPower, defenseRating, speed, range, miniaturizationLevel));
           }

           int numTechnologies;
           file >> numTechnologies;
           gameGalaxy.clearTechnologies();
           for (int i = 0; i < numTechnologies; ++i) {
               std::string name;
               int currentLevel, numEffects;
               double costToUpgrade;
               file >> name >> currentLevel >> costToUpgrade >> numEffects;
               Technology* tech = new Technology(name, currentLevel, costToUpgrade);
               for (int j = 0; j < numEffects; ++j) {
                   double effect;
                   file >> effect;
                   tech->addEffect(effect);
               }
               gameGalaxy.addTechnology(tech);
           }

           file.close();
           std::cout << "Game state loaded successfully!" << std::endl;
       } else {
           std::cout << "Unable to load game state. File could not be opened." << std::endl;
       }
   }

private:
   const Galaxy& gameGalaxy;
};

class AI {
public:
   AI(Galaxy& galaxy) : gameGalaxy(galaxy) {}

   void update(double deltaTime) {
       updateObservableGameState();
       makeDecisions();
       executeActions(deltaTime);
   }

   void updateObservableGameState() {
       observablePlanets.clear();
       for (Planet& planet : gameGalaxy.getPlanets()) {
           if (isVisible(planet)) {
               observablePlanets.push_back(planet);
           }
       }

       observableShips.clear();
       for (Ship& ship : gameGalaxy.getShips()) {
           if (isVisible(ship)) {
               observableShips.push_back(ship);
           }
       }

       observablePlayers.clear();
       for (Player& player : gameGalaxy.getPlayers()) {
           if (isVisible(player)) {
               observablePlayers.push_back(player);
           }
       }

       observableTechnologies.clear();
       for (Technology& technology : gameGalaxy.getTechnologies()) {
           if (isVisible(technology)) {
               observableTechnologies.push_back(technology);
           }
       }

       observableGameEvents.clear();
       for (GameEvent& event : gameGalaxy.getGameEvents()) {
           if (isVisible(event)) {
               observableGameEvents.push_back(event);
           }
       }
   }

   void makeDecisions() {
       analyzeObservableGameState();
       updateInternalState();
   }

   void executeActions(double deltaTime) {
       updateGameState(deltaTime);
   }

   void decidePlanetaryDevelopment() {
       for (Planet* planet : ownedPlanets) {
           double developmentPriority = assessPlanetPotential(planet);
           allocateResourcesForDevelopment(planet, developmentPriority);
           planPlanetaryDevelopment(planet, developmentPriority);
       }
   }

   void decideFleetMovement() {
       for (Fleet* fleet : ownedFleets) {
           double movementPriority = assessFleetObjectives(fleet);
           planFleetMovement(fleet, movementPriority);
       }
   }

   void decideResearch() {
       for (Technology* technology : availableTechnologies) {
           double researchPriority = assessTechnologyPotential(technology);
           allocateResearchPoints(technology, researchPriority);
       }
   }

   void decideDiplomacy() {
       for (Player* player : players) {
           if (player != aiPlayer) {
               double diplomaticPriority = assessDiplomaticStance(player);
               planDiplomaticActions(player, diplomaticPriority);
           }
       }
   }

   void developPlanets() {
       for (Planet* planet : ownedPlanets) {
           constructInfrastructure(planet);
           allocateResources(planet);
           managePopulation(planet);
       }
   }

   void moveFleets() {
       for (Fleet* fleet : ownedFleets) {
           moveFleetToTarget(fleet);
           engageInCombat(fleet);
       }
   }

   void conductResearch() {
       for (Technology* technology : availableTechnologies) {
           allocateResearchPoints(technology);
           updateResearchProgress(technology);
       }
   }

   void engageInDiplomacy() {
       for (Player* player : players) {
           if (player != aiPlayer) {
               proposeTreaty(player);
               proposeTradeAgreement(player);
               declareWar(player);
           }
       }
   }

private:
   Galaxy& gameGalaxy;
   Player* aiPlayer;
   std::vector<Planet*> ownedPlanets;
   std::vector<Fleet*> ownedFleets;
   std::vector<Technology*> availableTechnologies;
   std::vector<Player*> players;

   std::vector<Planet> observablePlanets;
   std::vector<Ship> observableShips;
   std::vector<Player> observablePlayers;
   std::vector<Technology> observableTechnologies;
   std::vector<GameEvent> observableGameEvents;

   // Placeholder functions for game state analysis and decision making
   bool isVisible(const Planet& planet) { return true; }
   bool isVisible(const Ship& ship) { return true; }
   bool isVisible(const Player& player) { return true; }
   bool isVisible(const Technology& technology) { return true; }
   bool isVisible(const GameEvent& event) { return true; }
   void analyzeObservableGameState() {}
   void updateInternalState() {}
   void updateGameState(double deltaTime) {}
   double assessPlanetPotential(Planet* planet) { return 0.0; }
   void allocateResourcesForDevelopment(Planet* planet, double priority) {}
   void planPlanetaryDevelopment(Planet* planet, double priority) {}
   double assessFleetObjectives(Fleet* fleet) { return 0.0; }
   void planFleetMovement(Fleet* fleet, double priority) {}
   double assessTechnologyPotential(Technology* technology) { return 0.0; }
   void allocateResearchPoints(Technology* technology, double priority) {}
   double assessDiplomaticStance(Player* player) { return 0.0; }
   void planDiplomaticActions(Player* player, double priority) {}
   void constructInfrastructure(Planet* planet) {}
   void allocateResources(Planet* planet) {}
   void managePopulation(Planet* planet) {}
   void moveFleetToTarget(Fleet* fleet) {}
   void engageInCombat(Fleet* fleet) {}
   void allocateResearchPoints(Technology* technology) {}
   void updateResearchProgress(Technology* technology) {}
   void proposeTreaty(Player* player) {}
   void proposeTradeAgreement(Player* player) {}
   void declareWar(Player* player) {}
};

class GameEvent {
public:
   void trigger() {
       if (isRandomEvent) {
           applyRandomEventEffects();
       }
       if (isStoryEvent) {
           displayStoryEventMessage();
           displayStoryEventChoices();
           handlePlayerChoice();
       }
       if (isDiplomaticEvent) {
           initiateDiplomaticNegotiations();
           triggerDiplomaticActions();
       }
   }

private:
   void applyRandomEventEffects() {
       if (isNaturalDisaster) {
           applyNaturalDisasterEffects();
       }
       if (isTechnologicalBreakthrough) {
           applyTechnologicalBreakthroughEffects();
       }
       if (isPirateAttack) {
           applyPirateAttackEffects();
       }
   }

   void displayStoryEventMessage() {
       std::cout << "A story event has occurred: " << eventMessage << std::endl;
   }

   void displayStoryEventChoices() {
       std::cout << "Choose an action:" << std::endl;
       for (int i = 0; i < choices.size(); ++i) {
           std::cout << i + 1 << ". " << choices[i] << std::endl;
       }
   }

   void handlePlayerChoice() {
       int choice;
       std::cin >> choice;
       applyChoiceEffects(choice);
   }

   void initiateDiplomaticNegotiations() {
       displayNegotiationOptions();
       handleNegotiationChoices();
   }

   void triggerDiplomaticActions() {
       if (isAllianceFormation) {
           formAlliance();
       }
       if (isTradeAgreement) {
           establishTradeAgreement();
       }
       if (isPeaceTreaty) {
           signPeaceTreaty();
       }
   }

   // Placeholder functions for event effects and actions
   void applyNaturalDisasterEffects() {}
   void applyTechnologicalBreakthroughEffects() {}
   void applyPirateAttackEffects() {}
   void applyChoiceEffects(int choice) {}
   void displayNegotiationOptions() {}
   void handleNegotiationChoices() {}
   void formAlliance() {}
   void establishTradeAgreement() {}
   void signPeaceTreaty() {}

   bool isRandomEvent = false;
   bool isStoryEvent = false;
   bool isDiplomaticEvent = false;
   bool isNaturalDisaster = false;
   bool isTechnologicalBreakthrough = false;
   bool isPirateAttack = false;
   bool isAllianceFormation = false;
   bool isTradeAgreement = false;
   bool isPeaceTreaty = false;
   std::string eventMessage;
   std::vector<std::string> choices;
};

class BattleSystem {
public:
   BattleSystem(Galaxy& galaxy) : gameGalaxy(galaxy) {}

   void initiateBattle(Player& attacker, Player& defender, Planet& battlePlanet) {
       this->attacker = &attacker;
       this->defender = &defender;
       this->battlePlanet = &battlePlanet;
       
       prepareShipsForBattle(attacker, attackerShips);
       prepareShipsForBattle(defender, defenderShips);

       round = 1;
   }

   void simulateBattle() {
       while (!isBattleOver()) {
           performBattleRound();
           displayRoundSummary();
           ++round;
       }
       determineBattleOutcome();
   }

   void displayBattleSummary() {
       std::cout << "Summary of battle at " << battlePlanet->getName() << " in " << gameGalaxy.getCurrentYear() << ":" << std::endl;
       std::cout << attacker->getName() << " vs. " << defender->getName() << std::endl;
       std::cout << "Round " << round << std::endl;

       displayShipStatus(attackerShips);
       displayShipStatus(defenderShips);

       displayBattleOutcome();
   }

private:
   Galaxy& gameGalaxy;
   Player* attacker;
   Player* defender;  
   Planet* battlePlanet;
   std::vector<Ship*> attackerShips;
   std::vector<Ship*> defenderShips;
   int round;

   void performBattleRound() {
       for (Ship* ship : attackerShips) {
           performShipAction(ship, defenderShips);
       }

       for (Ship* ship : defenderShips) {
           performShipAction(ship, attackerShips);
       }

       removeDestroyedShips(attackerShips);
       removeDestroyedShips(defenderShips);
   }

   void displayRoundSummary() {
       std::cout << "Round " << round << " summary:" << std::endl;

       displayShipActions(attackerShips);
       displayShipActions(defenderShips);
   }

   void determineBattleOutcome() {
       if (attackerShips.empty() && defenderShips.empty()) {
           std::cout << "The battle ended in a draw." << std::endl;
       } else if (attackerShips.empty()) {
           std::cout << defender->getName() << " wins the battle!" << std::endl;
           resolveBattleVictory(*defender, *battlePlanet);
       } else if (defenderShips.empty()) {
           std::cout << attacker->getName() << " wins the battle!" << std::endl;
           resolveBattleVictory(*attacker, *battlePlanet);
       }
   }

   void resolveBattleVictory(Player& victor, Planet& planet) {
       planet.setOwner(victor);
       applyBattleEffects(victor, planet);
       awardBattleRewards(victor, planet);
   }

   void prepareShipsForBattle(Player& player, std::vector<Ship*>& ships) {
       for (Ship* ship : player.getFleet()) {
           if (ship->isReadyForBattle()) {
               ships.push_back(ship);
           }
       }
   }

   void performShipAction(Ship* ship, std::vector<Ship*>& enemyShips) {
       Ship* target = selectTarget(enemyShips);
       ship->performAction(target);
   }

   void removeDestroyedShips(std::vector<Ship*>& ships) {
       ships.erase(std::remove_if(ships.begin(), ships.end(), [](Ship* ship) { return ship->isDestroyed(); }), ships.end());
   }

   void displayShipStatus(const std::vector<Ship*>& ships) {
       for (Ship* ship : ships) {
           std::cout << ship->getName() << " (" << ship->getHullStrength() << "/" << ship->getMaxHullStrength() << ")" << std::endl;
       }
   }

   void displayShipActions(const std::vector<Ship*>& ships) {
       for (Ship* ship : ships) {
           std::cout << ship->getName() << " performs " << ship->getLastAction() << std::endl;
       }
   }

   void applyBattleEffects(Player& victor, Planet& planet) {
       planet.applyBattleDamage();
       planet.applyPopulationLoss();

       for (Ship* ship : victor.getFleet()) {
           ship->gainExperience();
           ship->applyUpgrades();
       }
   }

   void awardBattleRewards(Player& victor, Planet& planet) {
       victor.addResources(planet.getResourceReward());
       victor.addTechnology(planet.getTechnologyReward());
       victor.addReputation(planet.getReputationReward());
   }

   Ship* selectTarget(const std::vector<Ship*>& enemyShips) {
       if (enemyShips.empty()) {
           return nullptr;
       }

       Ship* target = enemyShips[0];
       for (Ship* ship : enemyShips) {
           if (ship->getHullStrength() < target->getHullStrength()) {
               target = ship;
           }
       }

       return target;
   }

   bool isBattleOver() {
       return attackerShips.empty() || defenderShips.empty();
   }
};

class Game {
public:
   Game() {
       initializeGame();
   }

   void run() {
       while (!isGameOver) {
           double deltaTime = calculateDeltaTime();

           processInput();
           update(deltaTime);
           render();
       }
   }

   void initiateBattle(Player& attacker, Player& defender, Planet& planet) {
       BattleSystem battleSystem(gameGalaxy);
       battleSystem.initiateBattle(attacker, defender, planet);
       battleSystem.simulateBattle();
       battleSystem.displayBattleSummary();
   }

private:
   Galaxy gameGalaxy;
   std::vector<Player*> players;
   std::vector<AI*> aiPlayers;
   bool isGameOver;
   sf::RenderWindow window;
   sf::View view;
   sf::Clock clock;

   void initializeGame() {
       gameGalaxy = Galaxy();
       players = std::vector<Player*>();
       aiPlayers = std::vector<AI*>();
       isGameOver = false;

       window.create(sf::VideoMode(1024, 768), "Spaceward Ho!");
       view = window.getDefaultView();
   }

   void processInput() {
       sf::Event event;
       while (window.pollEvent(event)) {
           if (event.type == sf::Event::Closed) {
               window.close();
               isGameOver = true;
           } else if (event.type == sf::Event::KeyPressed) {
               handleKeyPress(event.key.code);
           } else if (event.type == sf::Event::MouseButtonPressed) {
               handleMouseClick(event.mouseButton);
           }
       }
   }

   void update(double deltaTime) {
       gameGalaxy.updateGameState(deltaTime);

       for (Player* player : players) {
           player->update(deltaTime);
       }

       for (AI* aiPlayer : aiPlayers) {
           aiPlayer->update(deltaTime);
       }

       handleEvents();
       triggerEvents();

       checkVictoryConditions();
   }

   void render() {
       window.clear();

       renderGalaxy();
       renderPlanets();
       renderShips();
       renderPlayers();
       renderUI();

       window.display();
   }

   double calculateDeltaTime() {
       return clock.restart().asSeconds();
   }

   void handleKeyPress(sf::Keyboard::Key key) {
       if (key == sf::Keyboard::Escape) {
           window.close();
           isGameOver = true;
       }
   }

   void handleMouseClick(const sf::Event::MouseButtonEvent& mouseButton) {
       if (mouseButton.button == sf::Mouse::Left) {
           sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Vector2i(mouseButton.x, mouseButton.y), view);
           handleLeftClick(mousePosition);
       } else if (mouseButton.button == sf::Mouse::Right) {
           sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Vector2i(mouseButton.x, mouseButton.y), view);
           handleRightClick(mousePosition);
       }
   }

   void handleLeftClick(const sf::Vector2f& position) {
       // Implement left click handling logic here
       // Example: Select a planet or ship at the clicked position
       // You can use the position parameter to determine what was clicked
       // and perform appropriate actions based on the game state and rules
   }

   void handleRightClick(const sf::Vector2f& position) {
   }

   void handleEvents() {
       for (GameEvent* event : gameGalaxy.getActiveEvents()) {
           event->handleEvent();
           updateGameState(event);
       }
   }

   void triggerEvents() {
       triggerRandomEvents();
       triggerStoryEvents();
       triggerDiplomaticEvents();
   }

   void checkVictoryConditions() {
       for (Player* player : players) {
           if (player->hasAchievedVictory()) {
               isGameOver = true;
               declareWinner(player);
               break;
           }
       }
   }

   void renderGalaxy() {
       sf::RectangleShape background(window.getView().getSize());
       background.setFillColor(sf::Color::Black);
       window.draw(background);

       for (const auto& star : gameGalaxy.getStars()) {
           sf::CircleShape starShape(2.0f);
           starShape.setFillColor(sf::Color::White);
           starShape.setPosition(star);
           window.draw(starShape);
       }
   }

   void renderPlanets() {
       for (Planet* planet : gameGalaxy.getPlanets()) {
           sf::CircleShape planetShape(planet->getRadius());
           planetShape.setFillColor(planet->getColor());
           planetShape.setPosition(planet->getPosition());
           window.draw(planetShape);
       }
   }

   void renderShips() {
       for (Ship* ship : gameGalaxy.getShips()) {
           sf::ConvexShape shipShape;
           shipShape.setPointCount(3);
           shipShape.setPoint(0, sf::Vector2f(0.0f, -10.0f));
           shipShape.setPoint(1, sf::Vector2f(-7.0f, 10.0f));
           shipShape.setPoint(2, sf::Vector2f(7.0f, 10.0f));
           shipShape.setFillColor(ship->getColor());
           shipShape.setPosition(ship->getPosition());
           shipShape.setRotation(ship->getRotation());
           window.draw(shipShape);
       }
   }

   void renderPlayers() {
       for (Player* player : players) {
           renderPlayerInfo(player);
       }
   }

   void renderUI() {
       renderPlayerResources();
       renderMinimap();
       renderSelectedItem();
   }

   void triggerRandomEvents() {
   }

   void triggerStoryEvents() {
   }

   void triggerDiplomaticEvents() {
   }

   void updateGameState(GameEvent* event) {
   }

   void declareWinner(Player* player) {
   }

   void renderPlayerInfo(Player* player) {
   }

   void renderPlayerResources() {
   }

   void renderMinimap() {
   }

   void renderSelectedItem() {
   }
};

int main() {
   Game game;
   game.run();
   return 0;
}

// Placeholder functions for utility and calculations
double randomDouble(double min, double max) {
   return min + (max - min) * (static_cast<double>(rand()) / RAND_MAX);
}

double calculateDistance(double x1, double y1, double x2, double y2) {
   double dx = x2 - x1;
   double dy = y2 - y1;
   return std::sqrt(dx * dx + dy * dy);
}

double calculateAngle(double x1, double y1, double x2, double y2) {
   double dx = x2 - x1;
   double dy = y2 - y1;
   return std::atan2(dy, dx);
}

double calculateRotationAngle(double currentAngle, double targetAngle) {
   double deltaAngle = targetAngle - currentAngle;
   if (deltaAngle > M_PI) {
       deltaAngle -= 2 * M_PI;
   } else if (deltaAngle < -M_PI) {
       deltaAngle += 2 * M_PI;
   }
   return deltaAngle;
}

double clamp(double value, double min, double max) {
   if (value < min) {
       return min;
   } else if (value > max) {
       return max;
   }
   return value;
}

int randomInt(int min, int max) {
   return min + rand() % (max - min + 1);
}

bool isInRange(double value, double min, double max) {
   return value >= min && value <= max;
}

// Placeholder functions for resource management
void Player::collectResources(double deltaTime) {
   for (Planet* planet : ownedPlanets) {
       double metalCollected = planet->calculateMetalProduction(deltaTime);
       double energyCollected = planet->calculateEnergyProduction(deltaTime);
       metal += metalCollected;
       energy += energyCollected;
   }
}

void Player::consumeResources(double metalCost, double energyCost) {
   if (metal >= metalCost && energy >= energyCost) {
       metal -= metalCost;
       energy -= energyCost;
   }
}

bool Player::canAfford(double metalCost, double energyCost) {
   return metal >= metalCost && energy >= energyCost;
}

// Placeholder functions for ship management
void Player::constructShip(const std::string& shipType) {
   if (canAfford(getShipMetalCost(shipType), getShipEnergyCost(shipType))) {
       consumeResources(getShipMetalCost(shipType), getShipEnergyCost(shipType));
       Ship ship(shipType);
       ownedShips.push_back(ship);
   }
}

void Player::issueFleetOrder(const std::vector<Ship*>& fleet, const FleetOrder& order) {
   for (Ship* ship : fleet) {
       ship->setOrder(order);
   }
}

void Ship::executeOrder(double deltaTime) {
   if (order.type == FleetOrder::MOVE_TO) {
       moveToTarget(order.target, deltaTime);
   } else if (order.type == FleetOrder::ATTACK) {
       attackTarget(order.target, deltaTime);
   } else if (order.type == FleetOrder::DEFEND) {
       defendPosition(order.target, deltaTime);
   }
}

void Ship::moveToTarget(const sf::Vector2f& target, double deltaTime) {
   sf::Vector2f direction = target - getPosition();
   double distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
   if (distance > 0.0) {
       sf::Vector2f velocity = direction / static_cast<float>(distance) * static_cast<float>(getSpeed());
       setPosition(getPosition() + velocity * static_cast<float>(deltaTime));
       setRotation(calculateAngle(getPosition().x, getPosition().y, target.x, target.y) * 180.0 / M_PI);
   }
}

void Ship::attackTarget(Ship* target, double deltaTime) {
   if (target != nullptr) {
       double distance = calculateDistance(getPosition().x, getPosition().y, target->getPosition().x, target->getPosition().y);
       if (distance <= getWeaponRange()) {
           double damage = calculateWeaponDamage();
           target->takeDamage(damage);
           weaponCooldown = getWeaponReloadTime();
       } else {
           moveToTarget(target->getPosition(), deltaTime);
       }
   }
}

void Ship::defendPosition(const sf::Vector2f& position, double deltaTime) {
   double distance = calculateDistance(getPosition().x, getPosition().y, position.x, position.y);
   if (distance > getDefenseRange()) {
       moveToTarget(position, deltaTime);
   }
}

void Ship::takeDamage(double damage) {
   shields -= damage;
   if (shields < 0) {
       double remainingDamage = -shields;
       shields = 0;
       health -= remainingDamage;
       if (health <= 0) {
           destroy();
       }
   }
}

void Ship::destroy() {
   setDestroyed(true);
}

double Ship::calculateWeaponDamage() {
   return getWeaponDamage();
}

// Placeholder functions for planet management
void Player::colonizePlanet(Planet* planet) {
   if (planet->getOwner() == nullptr && canAfford(getColonizationCost(planet))) {
       consumeResources(getColonizationCost(planet), 0.0);
       planet->setOwner(this);
       ownedPlanets.push_back(planet);
   }
}

void Player::developPlanet(Planet* planet, double metalInvestment, double energyInvestment) {
   if (planet->getOwner() == this && canAfford(metalInvestment, energyInvestment)) {
       consumeResources(metalInvestment, energyInvestment);
       planet->invest(metalInvestment, energyInvestment);
   }
}

void Planet::invest(double metalInvestment, double energyInvestment) {
   metalMines += metalInvestment;
   energyGenerators += energyInvestment;
}

double Planet::calculateMetalProduction(double deltaTime) {
   return metalMines * miningEfficiency * deltaTime;
}

double Planet::calculateEnergyProduction(double deltaTime) {
   return energyGenerators * energyEfficiency * deltaTime;
}

// Placeholder functions for technology research
void Player::researchTechnology(const std::string& techName) {
   if (canAfford(getTechMetalCost(techName), getTechEnergyCost(techName))) {
       consumeResources(getTechMetalCost(techName), getTechEnergyCost(techName));
       Technology* tech = gameState->getTechnology(techName);
       if (tech != nullptr) {
           tech->research(this);
       }
   }
}

void Technology::research(Player* player) {
   if (!isResearched()) {
       researchProgress += player->getResearchOutput();
       if (researchProgress >= researchCost) {
           setResearched(true);
           applyEffects(player);
       }
   }
}

void Technology::applyEffects(Player* player) {
   // Apply technology effects to the player
   if (name == "Advanced Mining") {
       for (Planet* planet : player->getOwnedPlanets()) {
           planet->increaseMiningEfficiency(0.1);
       }
   } else if (name == "Energy Efficiency") {
       for (Planet* planet : player->getOwnedPlanets()) {
           planet->increaseEnergyEfficiency(0.1);
       }
   } else if (name == "Weapons Upgrade") {
       for (Ship& ship : player->getOwnedShips()) {
           ship.upgradeWeapons(10.0);
       }
   } else if (name == "Shield Upgrade") {
       for (Ship& ship : player->getOwnedShips()) {
           ship.upgradeShields(50.0);
       }
   } else if (name == "Engine Upgrade") {
       for (Ship& ship : player->getOwnedShips()) {
           ship.upgradeSpeed(1.0);
       }
   } else if (name == "Planetary Defense") {
       for (Planet* planet : player->getOwnedPlanets()) {
           planet->upgradeDefenses(1.0);
       }
   } else if (name == "Population Growth") {
       for (Planet* planet : player->getOwnedPlanets()) {
           planet->increasePopulationGrowth(0.01);
       }
   }
}

// Placeholder functions for diplomacy and trade
void Player::proposeTrade(Player* otherPlayer, double metalOffer, double energyOffer, double metalRequest, double energyRequest) {
   if (canAfford(metalOffer, energyOffer)) {
       TradeOffer offer{metalOffer, energyOffer, metalRequest, energyRequest};
       otherPlayer->receiveTradeOffer(this, offer);
   }
}

void Player::receiveTradeOffer(Player* sender, const TradeOffer& offer) {
   // Evaluate the trade offer and decide whether to accept or reject it
   bool accepted = evaluateTradeOffer(offer);
   if (accepted) {
       acceptTradeOffer(sender, offer);
   } else {
       rejectTradeOffer(sender, offer);
   }
}

void Player::acceptTradeOffer(Player* sender, const TradeOffer& offer) {
   if (canAfford(offer.metalRequest, offer.energyRequest)) {
       consumeResources(offer.metalRequest, offer.energyRequest);
       sender->consumeResources(offer.metalOffer, offer.energyOffer);
       metal += offer.metalOffer;
       energy += offer.energyOffer;
       sender->metal += offer.metalRequest;
       sender->energy += offer.energyRequest;
   }
}

void Player::rejectTradeOffer(Player* sender, const TradeOffer& offer) {
   // Reject the trade offer
   // Notify the sender that the trade offer was rejected
   sender->handleTradeOfferRejection(this, offer);
}

bool Player::evaluateTradeOffer(const TradeOffer& offer) {
   // Evaluate the trade offer based on player's trade strategy and current needs
   // Consider factors such as resource balance, relationship with the sender, and long-term goals
   // Return true if the offer is acceptable, false otherwise
   
   // Example evaluation logic:
   if (offer.metalOffer >= offer.metalRequest && offer.energyOffer >= offer.energyRequest) {
       // The offer provides more resources than requested, so it is favorable
       return true;
   }
   
   // Additional evaluation criteria can be added here
   
   return false;
}

void Player::proposeDiplomacy(Player* otherPlayer, const std::string& proposalType) {
   if (proposalType == "ALLIANCE") {
       otherPlayer->receiveAllianceProposal(this);
   } else if (proposalType == "WAR") {
       otherPlayer->receiveWarDeclaration(this);
   } else if (proposalType == "PEACE") {
       otherPlayer->receivePeaceProposal(this);
   }
}

void Player::receiveAllianceProposal(Player* sender) {
   // Evaluate the alliance proposal and decide whether to accept or reject it
   bool accepted = evaluateAllianceProposal(sender);
   if (accepted) {
       acceptAlliance(sender);
   } else {
       rejectAlliance(sender);
   }
}

void Player::acceptAlliance(Player* otherPlayer) {
   // Form an alliance with the other player
   allies.push_back(otherPlayer);
   otherPlayer->allies.push_back(this);
}

void Player::rejectAlliance(Player* sender) {
   // Reject the alliance proposal
   // Notify the sender that the alliance proposal was rejected
   sender->handleAllianceRejection(this);
}

bool Player::evaluateAllianceProposal(Player* sender) {
   // Evaluate the alliance proposal based on player's diplomatic strategy and relationship with the sender
   // Consider factors like mutual benefits, shared enemies, and long-term strategic goals
   // Return true if the proposal is acceptable, false otherwise
   
   // Example evaluation logic:
   if (!isEnemy(sender) && !isAtWarWith(sender) && getRelationshipScore(sender) >= 50) {
       // The sender is not an enemy, not at war with the player, and has a good relationship score
       return true;
   }
   
   // Additional evaluation criteria can be added here
   
   return false;
}

void Player::receiveWarDeclaration(Player* sender) {
   // Handle the war declaration
   // Add the sender to the list of enemies
   enemies.push_back(sender);
   // Notify the player about the war declaration
   handleWarDeclaration(sender);
}
void Player::receivePeaceProposal(Player* sender) {
   // Evaluate the peace proposal and decide whether to accept or reject it
   bool accepted = evaluatePeaceProposal(sender);
   if (accepted) {
       acceptPeace(sender);
   } else {
       rejectPeace(sender);
   }
}

void Player::acceptPeace(Player* otherPlayer) {
   // Establish peace with the other player
   removeEnemy(otherPlayer);
   otherPlayer->removeEnemy(this);
}

bool Player::evaluatePeaceProposal(Player* sender) {
   // Evaluate the peace proposal based on player's diplomatic strategy and current relationship with the sender
   // Consider factors like relative military strength, war weariness, and potential benefits of peace
   // Return true if the proposal is acceptable, false otherwise
   
   // Example evaluation logic:
   if (isEnemy(sender) && getWarWeariness() >= 75 && getMilitaryStrength() <= sender->getMilitaryStrength()) {
       // The sender is an enemy, the player has high war weariness, and the sender has equal or greater military strength
       return true;
   }
   
   // Additional evaluation criteria can be added here
   
   return false;
}

void Player::removeEnemy(Player* enemy) {
   enemies.erase(std::remove(enemies.begin(), enemies.end(), enemy), enemies.end());
}

void GameEvent::trigger() {
   // Trigger the game event
   // Apply the effects of the game event
   applyEffects();
}

void GameEvent::applyEffects() {
   // Apply the effects of the game event based on its type
   if (isRandomEvent) {
       applyRandomEffects();
   } else if (isStoryEvent) {
       applyStoryEffects();
   } else if (isDiplomaticEvent) {
       applyDiplomaticEffects();
   }
}

void GameEvent::applyRandomEffects() {
   // Apply random event effects based on the event type and severity
   if (isNaturalDisaster) {
       applyNaturalDisasterEffects();
   } else if (isTechnologicalBreakthrough) {
       applyTechnologicalBreakthroughEffects();
   } else if (isPirateAttack) {
       applyPirateAttackEffects();
   }
}

void GameEvent::applyStoryEffects() {
   // Apply story event effects based on the event type and player choices
   // Display event message and choices to the player
   displayEventMessage();
   displayEventChoices();
   
   // Handle player's choice and apply corresponding effects
   int choice = getPlayerChoice();
   applyChoiceEffects(choice);
}

void GameEvent::applyDiplomaticEffects() {
   // Apply diplomatic event effects based on the event type and involved parties
   if (isAllianceProposal) {
       handleAllianceProposal();
   } else if (isTradeAgreement) {
       handleTradeAgreement();
   } else if (isPeaceTreaty) {
       handlePeaceTreaty();
   }
}

void GameEvent::displayEventMessage() {
   // Display the event message to the player
   std::cout << "A " << getEventType() << " event has occurred!" << std::endl;
   std::cout << getEventMessage() << std::endl;
}

void GameEvent::displayEventChoices() {
   // Display the available choices for the event
   std::cout << "Choose an action:" << std::endl;
   for (int i = 0; i < getNumChoices(); ++i) {
       std::cout << i + 1 << ". " << getChoice(i) << std::endl;
   }
}

int GameEvent::getPlayerChoice() {
   // Get the player's choice from input
   int choice;
   std::cin >> choice;
   return choice;
}

void GameEvent::applyChoiceEffects(int choice) {
   // Apply the effects based on the player's choice
   std::cout << "You selected choice " << choice << std::endl;
}

void GameEvent::handleAllianceProposal() {
   // Handle the alliance proposal event
   // Determine the involved players and initiate the proposal
   Player* proposingPlayer = getProposingPlayer();
   Player* receivingPlayer = getReceivingPlayer();
   receivingPlayer->receiveAllianceProposal(proposingPlayer);
}

void GameEvent::handleTradeAgreement() {
   // Handle the trade agreement event
   // Determine the involved players and initiate the trade negotiation
   Player* proposingPlayer = getProposingPlayer();
   Player* receivingPlayer = getReceivingPlayer();
   proposingPlayer->proposeTrade(receivingPlayer, getTradeOffer());
}

void GameEvent::handlePeaceTreaty() {
   // Handle the peace treaty event
   // Determine the involved players and initiate the peace proposal
   Player* proposingPlayer = getProposingPlayer();
   Player* receivingPlayer = getReceivingPlayer();
   proposingPlayer->proposePeace(receivingPlayer);
}

// Placeholder functions for game state management
void GameState::addEvent(GameEvent* event) {
   events.push_back(event);
}

void GameState::removeEvent(GameEvent* event) {
   events.erase(std::remove(events.begin(), events.end(), event), events.end());
}

void GameState::triggerEvents() {
   for (GameEvent* event : events) {
       event->trigger();
   }
}

void GameState::handleInput() {
   // Handle player input
   std::cout << "Handling player input..." << std::endl;
}

void GameState::update(double deltaTime) {
   // Update game state
   std::cout << "Updating game state..." << std::endl;
}

void GameState::render() {
   // Render game graphics
   std::cout << "Rendering game graphics..." << std::endl;
}

// Placeholder functions for utility and rendering
double getShipMetalCost(const std::string& shipType) {
   // Return the metal cost of constructing a ship of the given type
   return 100.0;
}

double getShipEnergyCost(const std::string& shipType) {
   // Return the energy cost of constructing a ship of the given type
   return 50.0;
}

double getColonizationCost(Planet* planet) {
   // Return the cost of colonizing the given planet
   return 500.0;
}

double getTechMetalCost(const std::string& techName) {
   // Return the metal cost of researching the given technology
   return 200.0;
}

double getTechEnergyCost(const std::string& techName) {
   // Return the energy cost of researching the given technology
   return 100.0;
}

void renderText(const std::string& text, int x, int y) {
   // Render text on the screen at the specified position
   std::cout << "Rendering text: " << text << " at (" << x << ", " << y << ")" << std::endl;
}

void renderRect(int x, int y, int width, int height, const sf::Color& color) {
   // Render a rectangle on the screen with the specified position, size, and color
   std::cout << "Rendering rectangle at (" << x << ", " << y << ") with size (" << width << ", " << height << ")" << std::endl;
}

void renderCircle(int x, int y, int radius, const sf::Color& color) {
   // Render a circle on the screen with the specified position, radius, and color
   std::cout << "Rendering circle at (" << x << ", " << y << ") with radius " << radius << std::endl;
}

void renderLine(int x1, int y1, int x2, int y2, const sf::Color& color) {
   // Render a line on the screen with the specified start and end positions and color
   std::cout << "Rendering line from (" << x1 << ", " << y1 << ") to (" << x2 << ", " << y2 << ")" << std::endl;
}

void renderTexture(const sf::Texture& texture, int x, int y) {
   // Render a texture on the screen at the specified position
   std::cout << "Rendering texture at (" << x << ", " << y << ")" << std::endl;
}

void playSound(const std::string& soundFile) {
   // Play the specified sound file
   std::cout << "Playing sound: " << soundFile << std::endl;
}

void playMusic(const std::string& musicFile) {
   // Play the specified music file
   std::cout << "Playing music: " << musicFile << std::endl;
}

// Implement additional utility and rendering functions as needed

// Placeholder functions for game flow control
void startNewGame() {
   // Start a new game
   std::cout << "Starting a new game..." << std::endl;
}

void loadGame(const std::string& saveFile) {
   // Load a saved game from the specified file
   std::cout << "Loading game from: " << saveFile << std::endl;
}

void saveGame(const std::string& saveFile) {
   // Save the current game state to the specified file
   std::cout << "Saving game to: " << saveFile << std::endl;
}

void showMainMenu() {
   // Display the main menu
   std::cout << "Showing main menu..." << std::endl;
}

void showPauseMenu() {
   // Display the pause menu
   std::cout << "Showing pause menu..." << std::endl;
}

void showGameOverScreen() {
   // Display the game over screen
   std::cout << "Showing game over screen..." << std::endl;
}

void exitGame() {
   // Exit the game
   std::cout << "Exiting the game..." << std::endl;
}

// Implement additional game flow control functions as needed

// Main function
int main() {
   // Initialize the game
   std::cout << "Initializing the game..." << std::endl;

   // Load game resources (textures, sounds, music, etc.)
   std::cout << "Loading game resources..." << std::endl;

   // Create the game window
   std::cout << "Creating the game window..." << std::endl;

   // Set up the game state
   GameState gameState;
   std::cout << "Setting up the game state..." << std::endl;

   // Game loop
   while (true) {
       // Handle events
       gameState.handleInput();

       // Update game state
       gameState.update(0.016); // Assuming 60 FPS

       // Render the game
       gameState.render();

       // Check for game over condition
       if (gameState.isGameOver()) {
           showGameOverScreen();
           break;
       }
   }

   // Clean up and exit
   std::cout << "Cleaning up and exiting..." << std::endl;

   return 0;
}

// Placeholder implementations for game classes and functions

// Player class
Player::Player(const std::string& name) : name(name) {}

std::string Player::getName() const {
   return name;
}

void Player::setResources(double metal, double energy) {
   this->metal = metal;
   this->energy = energy;
}

double Player::getMetal() const {
   return metal;
}

double Player::getEnergy() const {
   return energy;
}

void Player::addPlanet(Planet* planet) {
   ownedPlanets.push_back(planet);
}

void Player::removePlanet(Planet* planet) {
   ownedPlanets.erase(std::remove(ownedPlanets.begin(), ownedPlanets.end(), planet), ownedPlanets.end());
}

void Player::addShip(Ship ship) {
   ownedShips.push_back(ship);
}

void Player::removeShip(const Ship& ship) {
   ownedShips.erase(std::remove(ownedShips.begin(), ownedShips.end(), ship), ownedShips.end());
}

void Player::setResearchOutput(double researchOutput) {
   this->researchOutput = researchOutput;
}

double Player::getResearchOutput() const {
   return researchOutput;
}

void Player::addTechnology(Technology* technology) {
   researchedTechnologies.push_back(technology);
}

void Player::handleTradeOfferRejection(Player* sender, const TradeOffer& offer) {
   // Handle the rejection of a trade offer
   std::cout << "Trade offer rejected by " << sender->getName() << std::endl;
}

void Player::handleAllianceRejection(Player* sender) {
   // Handle the rejection of an alliance proposal
   std::cout << "Alliance proposal rejected by " << sender->getName() << std::endl;
}

void Player::handleWarDeclaration(Player* enemy) {
   // Handle the declaration of war by an enemy
   std::cout << "War declared by " << enemy->getName() << std::endl;
}

void Player::handlePeaceRejection(Player* enemy) {
   // Handle the rejection of a peace proposal
   std::cout << "Peace proposal rejected by " << enemy->getName() << std::endl;
}

bool Player::isEnemy(Player* player) {
   return std::find(enemies.begin(), enemies.end(), player) != enemies.end();
}

bool Player::isAtWarWith(Player* player) {
   return std::find(enemies.begin(), enemies.end(), player) != enemies.end();
}

int Player::getRelationshipScore(Player* player) {
   // Get the relationship score with the specified player
   auto it = std::find_if(relationships.begin(), relationships.end(), [player](const PlayerRelationship& relationship) {
      return relationship.player == player;
   });

   if (it != relationships.end()) {
      return it->score;
   }

   return 0;
}

int Player::getWarWeariness() {
   // Calculate and return the player's war weariness level based on factors such as duration of ongoing wars, losses suffered, etc.
   int warWeariness = 0;

   for (const auto& war : ongoingWars) {
      int warDuration = getCurrentTurn() - war.startTurn;
      int losses = war.getPlayerLosses(this);
      warWeariness += warDuration * losses;
   }

   return warWeariness;
}

int Player::getMilitaryStrength() {
   // Calculate and return the player's military strength based on factors such as number and strength of ships, technologies researched, etc.
   int militaryStrength = 0;

   for (const auto& ship : ownedShips) {
      militaryStrength += ship.getStrength();
   }

   for (const auto& technology : researchedTechnologies) {
      if (technology->isMilitary()) {
         militaryStrength += technology->getMilitaryBonus();
      }
   }

   return militaryStrength;
}

void Player::proposePeace(Player* player) {
   // Check if the player is currently at war with the specified player
   if (isAtWarWith(player)) {
      // Send a peace proposal to the specified player
      // Implementation of sending peace proposal
      std::cout << "Proposing peace to " << player->getName() << std::endl;
   }
}

// Implement additional functions for the Player class as needed

// Planet class
Planet::Planet(int x, int y, int owner, int population, double temperature, double gravity, double metal)
   : x(x), y(y), owner(owner), population(population), temperature(temperature), gravity(gravity), metal(metal) {}

int Planet::getX() const {
   return x;
}

int Planet::getY() const {
   return y;
}

int Planet::getOwner() const {
   return owner;
}

void Planet::setOwner(int owner) {
   this->owner = owner;
}

int Planet::getPopulation() const {
   return population;
}

void Planet::setPopulation(int population) {
   this->population = population;
}

double Planet::getTemperature() const {
   return temperature;
}

double Planet::getGravity() const {
   return gravity;
}

double Planet::getMetal() const {
   return metal;
}

void Planet::setMetal(double metal) {
   this->metal = metal;
}

int Planet::getTerraformingLevel() const {
   return terraformingLevel;
}

void Planet::setTerraformingLevel(int level) {
   terraformingLevel = level;
}

int Planet::getMiningLevel() const {
   return miningLevel;
}

void Planet::setMiningLevel(int level) {
   miningLevel = level;
}

int Planet::getShipbuildingCapacity() const {
   return shipbuildingCapacity;
}

void Planet::setShipbuildingCapacity(int capacity) {
   shipbuildingCapacity = capacity;
}

int Planet::getDefenseLevel() const {
   return defenseLevel;
}

void Planet::setDefenseLevel(int level) {
   defenseLevel = level;
}

void Planet::increaseMiningEfficiency(double amount) {
   miningEfficiency += amount;
}

void Planet::increaseEnergyEfficiency(double amount) {
   energyEfficiency += amount;
}

void Planet::upgradeDefenses(double amount) {
   defenseLevel += amount;
}

void Planet::increasePopulationGrowth(double amount) {
   populationGrowthRate += amount;
}

double Planet::getColonizationCost() const {
   // Calculate and return the colonization cost for the planet based on its attributes
   double baseCost = 1000.0;
   double terraformingCost = terraformingLevel * 100.0;
   double miningCost = miningLevel * 50.0;
   double shipbuildingCost = shipbuildingCapacity * 200.0;
   double defenseCost = defenseLevel * 150.0;
   
   double totalCost = baseCost + terraformingCost + miningCost + shipbuildingCost + defenseCost;
   return totalCost;
}

// Implement additional functions for the Planet class as needed

// Ship class
class Ship {
private:
   std::string type;
   int health;
   int attackPower;
   int speed;

public:
   Ship(const std::string& type, int health, int attackPower, int speed);
   std::string getType() const;
   int getHealth() const;
   int getAttackPower() const;
   int getSpeed() const;
   void takeDamage(int amount);
   bool isDestroyed() const;
};

Ship::Ship(const std::string& type, int health, int attackPower, int speed)
   : type(type), health(health), attackPower(attackPower), speed(speed) {}

std::string Ship::getType() const {
   return type;
}

int Ship::getHealth() const {
   return health;
}

int Ship::getAttackPower() const {
   return attackPower;
}

int Ship::getSpeed() const {
   return speed;
}

void Ship::takeDamage(int amount) {
   health -= amount;
}

bool Ship::isDestroyed() const {
   return health <= 0;
}

double Ship::getWeaponDamage() const {
   // Calculate and return the ship's weapon damage
   return weaponDamage;
}

double Ship::getWeaponRange() const {
   // Calculate and return the ship's weapon range
   return weaponRange;
}

double Ship::getDefenseRating() const {
   // Calculate and return the ship's defense rating
   return defenseRating;
}

double Ship::getSpeed() const {
   // Calculate and return the ship's speed
   return speed;
}

sf::Vector2f Ship::getPosition() const {
   return position;
}

void Ship::setPosition(const sf::Vector2f& pos) {
   position = pos;
}

double Ship::getRotation() const {
   return rotation;
}

void Ship::setRotation(double angle) {
   rotation = angle;
}

void Ship::setOrder(const FleetOrder& order) {
   currentOrder = order;
}

bool Ship::isReadyForBattle() const {
   // Check if the ship is ready for battle
   return !isDestroyed() && getWeaponReloadTime() == 0;
}

void Ship::performAction(Ship* target) {
   if (isReadyForBattle()) {
      // Perform an action on the target ship
      std::cout << "Performing action on target ship" << std::endl;
      lastAction = "Attacked target ship";
   } else {
      std::cout << "Ship is not ready for battle" << std::endl;
   }
}

std::string Ship::getLastAction() const {
   return lastAction;
}

bool Ship::isDestroyed() const {
   return destroyed;
}

void Ship::setDestroyed(bool destroyedState) {
   destroyed = destroyedState;
}

int Ship::getWeaponReloadTime() const {
   return weaponReloadTime;
}

void Ship::setWeaponReloadTime(int time) {
   weaponReloadTime = time;
}

void Ship::upgradeWeapons(double amount) {
   // Upgrade the ship's weapons by the specified amount
   std::cout << "Upgrading weapons by " << amount << std::endl;
   weaponDamage += amount;
}

void Ship::upgradeShields(double amount) {
   // Upgrade the ship's shields by the specified amount
   std::cout << "Upgrading shields by " << amount << std::endl;
   defenseRating += amount;
}

void Ship::upgradeSpeed(double amount) {
   // Upgrade the ship's speed by the specified amount
   std::cout << "Upgrading speed by " << amount << std::endl;
   speed += amount;
}

// Implement additional functions for the Ship class as needed

// Technology class
Technology::Technology(const std::string& name, int level, double cost)
   : name(name), level(level), researchCost(cost), researchProgress(0.0) {}

std::string Technology::getName() const {
   return name;
}

int Technology::getLevel() const {
   return level;
}

double Technology::getResearchCost() const {
   return researchCost;
}

double Technology::getResearchProgress() const {
   return researchProgress;
}

void Technology::setResearchProgress(double progress) {
   researchProgress = progress;
}

bool Technology::isResearched() const {
   return researchProgress >= researchCost;
}

void Technology::setResearched(bool researched) {
   if (researched) {
      researchProgress = researchCost;
   } else {
      researchProgress = 0.0;
   }
}

// Implement as needed by inserting functional statements:
int Technology::getMetalCost() const {
   // Get the metal cost of the technology
   return static_cast<int>(researchCost * 0.6);
}

int Technology::getEnergyCost() const {
   // Get the energy cost of the technology
   return static_cast<int>(researchCost * 0.4);
}

// Implement additional functions for the Technology class as needed

// GameState class
bool GameState::isGameOver() const {
   // Check if the game is over
   return false;
}

// Implement additional functions for the GameState class as needed

// Fleet class
void Fleet::addShip(const Ship& ship) {
   ships.push_back(ship);
}

void Fleet::removeShip(const Ship& ship) {
   ships.erase(std::remove(ships.begin(), ships.end(), ship), ships.end());
}

// Implement additional functions for the Fleet class as needed

// EspionageMission class
bool EspionageMission::isCompleted() const {
   // Check if the espionage mission is completed
   return elapsedTime >= duration;
}

// TradeOffer struct
struct TradeOffer {
   double metalOffer;
   double energyOffer;
   double metalRequest;
   double energyRequest;
};

// Implement additional structs as needed
Player* GameEvent::getProposingPlayer() const {
   // Get the player proposing the event
   return proposingPlayer;
}

Player* GameEvent::getReceivingPlayer() const {
   // Get the player receiving the event
   return receivingPlayer;
}

TradeOffer GameEvent::getTradeOffer() const {
   // Get the trade offer associated with the event
   return tradeOffer;
}

std::string GameEvent::getEventType() const {
    if (isRandomEvent) {
       if (isNaturalDisaster) {
           return "Natural Disaster";
       } else if (isTechnologicalBreakthrough) {
           return "Technological Breakthrough";
       } else if (isPirateAttack) {
           return "Pirate Attack";
       }
   } else if (isStoryEvent) {
       return "Story Event";
   } else if (isDiplomaticEvent) {
       if (isAllianceProposal) {
           return "Alliance Proposal";
       } else if (isTradeAgreement) {
           return "Trade Agreement";
       } else if (isPeaceTreaty) {
           return "Peace Treaty";
       }
   }
   return "Unknown Event";
}

std::string GameEvent::getEventMessage() const {
   return eventMessage;
}

int GameEvent::getNumChoices() const {
   return choices.size();
}

std::string GameEvent::getChoice(int index) const {
   if (index >= 0 && index < choices.size()) {
       return choices[index];
   }
   return "";
}

void GameEvent::applyNaturalDisasterEffects() {
   for (Planet* planet : gameState->getPlanets()) {
       double damageChance = randomDouble(0.0, 1.0);
       if (damageChance < 0.5) {
           double damageAmount = randomDouble(0.1, 0.3);
           planet->applyDamage(damageAmount);
       }
   }
}

void GameEvent::applyTechnologicalBreakthroughEffects() {
   for (Player* player : gameState->getPlayers()) {
       Technology* randomTech = gameState->getRandomUnresearchedTechnology();
       if (randomTech != nullptr) {
           randomTech->setResearched(true);
           player->addTechnology(randomTech);
       }
   }
}

void GameEvent::applyPirateAttackEffects() {
   for (Player* player : gameState->getPlayers()) {
       double attackChance = randomDouble(0.0, 1.0);
       if (attackChance < 0.5) {
           double stolenResources = player->getMetal() * randomDouble(0.1, 0.2);
           player->setMetal(player->getMetal() - stolenResources);
           double stolenEnergy = player->getEnergy() * randomDouble(0.1, 0.2);
           player->setEnergy(player->getEnergy() - stolenEnergy);
       }
   }
}

void GameState::getPlanets() {
   return planets;
}

std::vector<Player*> GameState::getPlayers() {
   return players;
}

Technology* GameState::getRandomUnresearchedTechnology() {
   std::vector<Technology*> unresearchedTechs;
   for (Technology* tech : technologies) {
       if (!tech->isResearched()) {
           unresearchedTechs.push_back(tech);
       }
   }
   if (!unresearchedTechs.empty()) {
       int randomIndex = randomInt(0, unresearchedTechs.size() - 1);
       return unresearchedTechs[randomIndex];
   }
   return nullptr;
}

void Planet::applyDamage(double damageAmount) {
   population -= static_cast<int>(population * damageAmount);
   if (population < 0) {
       population = 0;
   }
   double infrastructureDamage = damageAmount * 0.5;
   double miningDamage = damageAmount * 0.3;
   double energyDamage = damageAmount * 0.2;
   infrastructure -= infrastructureDamage;
   if (infrastructure < 0.0) {
       infrastructure = 0.0;
   }
   miningEfficiency -= miningDamage;
   if (miningEfficiency < 0.0) {
       miningEfficiency = 0.0;
   }
   energyEfficiency -= energyDamage;
   if (energyEfficiency < 0.0) {
       energyEfficiency = 0.0;
   }
}

void Game::handleKeyPress(sf::Keyboard::Key key) {
   if (key == sf::Keyboard::Escape) {
       showPauseMenu();
   } else if (key == sf::Keyboard::Space) {
       if (isPaused) {
           resumeGame();
       } else {
           pauseGame();
       }
   } else if (key == sf::Keyboard::F5) {
       quickSaveGame();
   } else if (key == sf::Keyboard::F9) {
       quickLoadGame();
   }
}

void Game::showPauseMenu() {
   pauseGame();
   isGamePaused = true;
}

void Game::pauseGame() {
   isPaused = true;
}

void Game::resumeGame() {
   isPaused = false;
   isGamePaused = false;
}

void Game::quickSaveGame() {
   saveGame("quicksave.sav");
}

void Game::quickLoadGame() {
   loadGame("quicksave.sav");
}

void Galaxy::getStars() const {
   return stars;
}

sf::Color Planet::getColor() const {
   if (owner == 0) {
       return sf::Color::Blue;
   } else if (owner == 1) {
       return sf::Color::Red;
   } else if (owner == 2) {
       return sf::Color::Green;
   } else {
       return sf::Color::Yellow;
   }
}

double Planet::getRadius() const {
   double baseRadius = 10.0;
   double populationFactor = std::log10(population + 1.0);
   double radiusMultiplier = 1.0 + populationFactor * 0.1;
   return baseRadius * radiusMultiplier;
}

sf::Vector2f Planet::getPosition() const {
   return sf::Vector2f(x, y);
}

sf::Color Ship::getColor() const {
   if (getOwner() == 0) {
       return sf::Color(128, 128, 255);
   } else if (getOwner() == 1) {
       return sf::Color(255, 128, 128);
   } else if (getOwner() == 2) {
       return sf::Color(128, 255, 128);
   } else {
       return sf::Color(255, 255, 128);
   }
}

int Ship::getOwner() const {
   return owner;
}

void Game::renderPlayerInfo(Player* player) {
   int x = 10;
   int y = 10;
   std::string playerName = player->getName();
   renderText(playerName, x, y);
   y += 20;
   std::string resourceInfo = "Metal: " + std::to_string(player->getMetal()) +
                              " Energy: " + std::to_string(player->getEnergy());
   renderText(resourceInfo, x, y);
   y += 20;
   std::string planetInfo = "Planets: " + std::to_string(player->getOwnedPlanets().size());
   renderText(planetInfo, x, y);
   y += 20;
   std::string shipInfo = "Ships: " + std::to_string(player->getOwnedShips().size());
   renderText(shipInfo, x, y);
   y += 20;
   std::string technologyInfo = "Technologies: " + std::to_string(player->getResearchedTechnologies().size());
   renderText(technologyInfo, x, y);
}

void Game::renderPlayerResources() {
   int x = 10;
   int y = 200;
   for (Player* player : players) {
       std::string resourceInfo = player->getName() + " - Metal: " + std::to_string(player->getMetal()) +
                                  " Energy: " + std::to_string(player->getEnergy());
       renderText(resourceInfo, x, y);
       y += 20;
   }
}

void Game::renderMinimap() {
   int minimapX = 800;
   int minimapY = 600;
   int minimapWidth = 200;
   int minimapHeight = 150;
   renderRect(minimapX, minimapY, minimapWidth, minimapHeight, sf::Color(128, 128, 128));
   for (Planet* planet : gameGalaxy.getPlanets()) {
       int planetX = minimapX + (planet->getX() * minimapWidth) / 1000;
       int planetY = minimapY + (planet->getY() * minimapHeight) / 1000;
       int planetRadius = 2;
       renderCircle(planetX, planetY, planetRadius, planet->getColor());
   }
}

void Game::renderSelectedItem() {
   if (selectedPlanet != nullptr) {
       int x = 500;
       int y = 10;
       std::string planetInfo = "Selected Planet: (" + std::to_string(selectedPlanet->getX()) + ", " +
                                std::to_string(selectedPlanet->getY()) + ")";
       renderText(planetInfo, x, y);
       y += 20;
       std::string ownerInfo = "Owner: " + std::to_string(selectedPlanet->getOwner());
       renderText(ownerInfo, x, y);
       y += 20;
       std::string populationInfo = "Population: " + std::to_string(selectedPlanet->getPopulation());
       renderText(populationInfo, x, y);
   } else if (selectedShip != nullptr) {
       int x = 500;
       int y = 10;
       std::string shipInfo = "Selected Ship: " + selectedShip->getType();
       renderText(shipInfo, x, y);
       y += 20;
       std::string ownerInfo = "Owner: " + std::to_string(selectedShip->getOwner());
       renderText(ownerInfo, x, y);
       y += 20;
       std::string positionInfo = "Position: (" + std::to_string(selectedShip->getPosition().x) + ", " +
                                  std::to_string(selectedShip->getPosition().y) + ")";
       renderText(positionInfo, x, y);
   }
}

void Game::triggerRandomEvents() {
   double eventChance = randomDouble(0.0, 1.0);
   if (eventChance < 0.1) {
       int eventType = randomInt(0, 2);
       if (eventType == 0) {
           GameEvent* event = new GameEvent();
           event->isRandomEvent = true;
           event->isNaturalDisaster = true;
           event->eventMessage = "A natural disaster has occurred!";
           gameState->addEvent(event);
       } else if (eventType == 1) {
           GameEvent* event = new GameEvent();
           event->isRandomEvent = true;
           event->isTechnologicalBreakthrough = true;
           event->eventMessage = "A technological breakthrough has been achieved!";
           gameState->addEvent(event);
       } else if (eventType == 2) {
           GameEvent* event = new GameEvent();
           event->isRandomEvent = true;
           event->isPirateAttack = true;
           event->eventMessage = "Pirates have attacked!";
           gameState->addEvent(event);
       }
   }
}

void Game::triggerStoryEvents() {
   double eventChance = randomDouble(0.0, 1.0);
   if (eventChance < 0.05) {
       GameEvent* event = new GameEvent();
       event->isStoryEvent = true;
       event->eventMessage = "A story event has occurred!";
       event->choices.push_back("Choice 1");
       event->choices.push_back("Choice 2");
       event->choices.push_back("Choice 3");
       gameState->addEvent(event);
   }
}

void Game::triggerDiplomaticEvents() {
   double eventChance = randomDouble(0.0, 1.0);
   if (eventChance < 0.05) {
       int eventType = randomInt(0, 2);
       if (eventType == 0) {
           GameEvent* event = new GameEvent();
           event->isDiplomaticEvent = true;
           event->isAllianceProposal = true;
           event->eventMessage = "An alliance has been proposed!";
           gameState->addEvent(event);
       } else if (eventType == 1) {
           GameEvent* event = new GameEvent();
           event->isDiplomaticEvent = true;
           event->isTradeAgreement = true;
           event->eventMessage = "A trade agreement has been proposed!";
           gameState->addEvent(event);
       } else if (eventType == 2) {
           GameEvent* event = new GameEvent();
           event->isDiplomaticEvent = true;
           event->isPeaceTreaty = true;
           event->eventMessage = "A peace treaty has been proposed!";
           gameState->addEvent(event);
       }
   }
}

void Game::updateGameState(GameEvent* event) {
   if (event->isRandomEvent) {
       if (event->isNaturalDisaster) {
           event->applyNaturalDisasterEffects();
       } else if (event->isTechnologicalBreakthrough) {
           event->applyTechnologicalBreakthroughEffects();
       } else if (event->isPirateAttack) {
           event->applyPirateAttackEffects();
       }
   } else if (event->isStoryEvent) {
       event->applyStoryEffects();
   } else if (event->isDiplomaticEvent) {
       event->applyDiplomaticEffects();
   }
}

void Game::declareWinner(Player* player) {
   std::string message = "Player " + player->getName() + " has won the game!";
   renderText(message, 400, 300);
}

void BattleSystem::handleLootDistribution(Player& victor, Planet& planet) {
   double lootChance = randomDouble(0.0, 1.0);
   if (lootChance < 0.5) {
       double metalLoot = planet.getMetal() * randomDouble(0.1, 0.3);
       double energyLoot = planet.getEnergy() * randomDouble(0.1, 0.3);
       victor.setMetal(victor.getMetal() + metalLoot);
       victor.setEnergy(victor.getEnergy() + energyLoot);
       planet.setMetal(planet.getMetal() - metalLoot);
       planet.setEnergy(planet.getEnergy() - energyLoot);
   }
}

void BattleSystem::updatePlanetOwnership(Player& victor, Planet& planet) {
   planet.setOwner(victor.getPlayerNumber());
}

void Player::removeEnemy(Player* enemy) {
   enemies.erase(std::remove(enemies.begin(), enemies.end(), enemy), enemies.end());
}

void Player::addAlly(Player* ally) {
   allies.push_back(ally);
}

void Player::removeAlly(Player* ally) {
   allies.erase(std::remove(allies.begin(), allies.end(), ally), allies.end());
}

bool Player::isAlly(Player* player) {
   return std::find(allies.begin(), allies.end(), player) != allies.end();
}

void Player::updateRelationshipScore(Player* player, int score) {
   relationshipScores[player] = score;
}

int Player::getRelationshipScore(Player* player) {
   return relationshipScores[player];
}

void Player::setWarWeariness(int weariness) {
   warWeariness = weariness;
}

int Player::getWarWeariness() {
   return warWeariness;
}

void Player::updateMilitaryStrength(int strength) {
   militaryStrength = strength;
}

int Player::getMilitaryStrength() {
   return militaryStrength;
}

void Player::updateEspionageEffectiveness(int effectiveness) {
   espionageEffectiveness = effectiveness;
}

int Player::getEspionageEffectiveness() {
   return espionageEffectiveness;
}

void Player::conductEspionage(Player* targetPlayer) {
   int espionageRoll = randomInt(0, 100);
   int espionageThreshold = 50 + targetPlayer->getCounterEspionageEffectiveness() - espionageEffectiveness;
   if (espionageRoll >= espionageThreshold) {
       stealResources(targetPlayer);
       stealTechnology(targetPlayer);
       gainIntel(targetPlayer);
   } else {
       failEspionage(targetPlayer);
   }
}

void Player::stealResources(Player* targetPlayer) {
   double stolenMetal = targetPlayer->getMetal() * randomDouble(0.05, 0.1);
   double stolenEnergy = targetPlayer->getEnergy() * randomDouble(0.05, 0.1);
   targetPlayer->setMetal(targetPlayer->getMetal() - stolenMetal);
   targetPlayer->setEnergy(targetPlayer->getEnergy() - stolenEnergy);
   metal += stolenMetal;
   energy += stolenEnergy;
}

void Player::stealTechnology(Player* targetPlayer) {
   if (!targetPlayer->getResearchedTechnologies().empty()) {
       int randomIndex = randomInt(0, targetPlayer->getResearchedTechnologies().size() - 1);
       Technology* stolenTech = targetPlayer->getResearchedTechnologies()[randomIndex];
       if (!hasTechnology(stolenTech)) {
           researchedTechnologies.push_back(stolenTech);
       }
   }
}

void Player::gainIntel(Player* targetPlayer) {
   int intelGained = randomInt(1, 5);
   std::cout << "Gained " << intelGained << " intel on " << targetPlayer->getName() << std::endl;
}

void Player::failEspionage(Player* targetPlayer) {
   int penaltyChance = randomInt(0, 100);
   if (penaltyChance < 50) {
       double resourcePenalty = getMetal() * randomDouble(0.05, 0.1);
       metal -= resourcePenalty;
       energy -= resourcePenalty;
   } else {
       int relationshipPenalty = randomInt(5, 15);
       int currentRelationship = getRelationshipScore(targetPlayer);
       updateRelationshipScore(targetPlayer, currentRelationship - relationshipPenalty);
   }
}

int Player::getCounterEspionageEffectiveness() {
   return counterEspionageEffectiveness;
}

bool Player::hasTechnology(Technology* technology) {
   return std::find(researchedTechnologies.begin(), researchedTechnologies.end(), technology) != researchedTechnologies.end();
}

void Player::setCounterEspionageEffectiveness(int effectiveness) {
   counterEspionageEffectiveness = effectiveness;
}

void Player::updateDiplomaticRelations(Player* player, int change) {
   int currentRelationship = getRelationshipScore(player);
   updateRelationshipScore(player, currentRelationship + change);
}

void Player::initiateDiplomaticMeeting(Player* player) {
   int relationshipScore = getRelationshipScore(player);
   if (relationshipScore >= 80) {
       proposeAlliance(player);
   } else if (relationshipScore >= 60) {
       proposeTrade(player);
   } else if (relationshipScore <= 20) {
       declareWar(player);
   } else {
       improveDiplomaticRelations(player);
   }
}

void Player::proposeAlliance(Player* player) {
   std::cout << "Proposing alliance to " << player->getName() << std::endl;
   int acceptanceChance = calculateAllianceAcceptanceChance(player);
   if (randomInt(0, 100) < acceptanceChance) {
       formAlliance(player);
   } else {
       std::cout << player->getName() << " rejected the alliance proposal." << std::endl;
   }
}

void Player::proposeTrade(Player* player) {
   std::cout << "Proposing trade to " << player->getName() << std::endl;
   int acceptanceChance = calculateTradeAcceptanceChance(player);
   if (randomInt(0, 100) < acceptanceChance) {
       conductTrade(player);
   } else {
       std::cout << player->getName() << " rejected the trade proposal." << std::endl;
   }
}

void Player::declareWar(Player* player) {
   std::cout << "Declaring war on " << player->getName() << std::endl;
   updateRelationshipScore(player, -50);
   player->updateRelationshipScore(this, -50);
   addEnemy(player);
   player->addEnemy(this);
}

void Player::formAlliance(Player* player) {
   std::cout << "Forming alliance with " << player->getName() << std::endl;
   updateRelationshipScore(player, 100);
   player->updateRelationshipScore(this, 100);
   addAlly(player);
   player->addAlly(this);
}

void Player::conductTrade(Player* player) {
   std::cout << "Conducting trade with " << player->getName() << std::endl;
   double tradeAmount = calculateTradeAmount(player);
   double metalTraded = tradeAmount * randomDouble(0.4, 0.6);
   double energyTraded = tradeAmount - metalTraded;
   metal -= metalTraded;
   energy -= energyTraded;
   player->metal += metalTraded;
   player->energy += energyTraded;
}

void Player::improveDiplomaticRelations(Player* player) {
   std::cout << "Improving diplomatic relations with " << player->getName() << std::endl;
   int improvementAmount = randomInt(5, 15);
   updateRelationshipScore(player, getRelationshipScore(player) + improvementAmount);
}

int Player::calculateAllianceAcceptanceChance(Player* player) {
   int relationshipScore = getRelationshipScore(player);
   int acceptanceChance = relationshipScore - 50;
   return std::max(0, std::min(acceptanceChance, 100));
}

int Player::calculateTradeAcceptanceChance(Player* player) {
   int relationshipScore = getRelationshipScore(player);
   int acceptanceChance = relationshipScore;
   return std::max(0, std::min(acceptanceChance, 100));
}

double Player::calculateTradeAmount(Player* player) {
   double tradeAmount = std::min(metal, energy) * randomDouble(0.1, 0.3);
   return tradeAmount;
}

void Player::updatePlanetUpgrades(Planet* planet) {
   int infrastructureUpgrade = randomInt(0, 2);
   int miningUpgrade = randomInt(0, 2);
   int researchUpgrade = randomInt(0, 2);
   int shipbuildingUpgrade = randomInt(0, 2);
   int defenseUpgrade = randomInt(0, 2);
   planet->infrastructure += infrastructureUpgrade;
   planet->miningEfficiency += miningUpgrade * 0.1;
   planet->energyEfficiency += researchUpgrade * 0.1;
   planet->shipbuildingCapacity += shipbuildingUpgrade;
   planet->defenseLevel += defenseUpgrade;
}

void Player::updateShipUpgrades(Ship* ship) {
   int weaponUpgrade = randomInt(0, 2);
   int shieldUpgrade = randomInt(0, 2);
   int engineUpgrade = randomInt(0, 2);
   ship->attackPower += weaponUpgrade * 5;
   ship->defenseRating += shieldUpgrade * 5;
   ship->speed += engineUpgrade * 0.1;
}

void Player::updateTechnologyUpgrades(Technology* technology) {
   int currentLevel = technology->getLevel();
   int maxLevel = 5;
   if (currentLevel < maxLevel) {
       int upgradeChance = randomInt(0, 100);
       if (upgradeChance < 50) {
           technology->setLevel(currentLevel + 1);
           std::cout << "Technology upgraded: " << technology->getName() << " to level " << technology->getLevel() << std::endl;
       }
   }
}

void Player::setName(const std::string& name) {
   playerName = name;
}

int Player::getShipCount() const {
   return ownedShips.size();
}

int Player::getPlanetCount() const {
   return ownedPlanets.size();
}

void Player::setResearchOutput(double output) {
   researchOutput = output;
}

void Projectile::setDamage(double damage) {
   this->damage = damage;
}

double Projectile::getDamage() const {
   return damage;
}

void Projectile::setSpeed(double speed) {
   this->speed = speed;
}

double Projectile::getSpeed() const {
   return speed;
}

void Projectile::setTarget(Ship* target) {
   this->target = target;
}

Ship* Projectile::getTarget() const {
   return target;
}

void Projectile::setSource(Ship* source) {
   this->source = source;
}

Ship* Projectile::getSource() const {
   return source;
}

void Projectile::update(double deltaTime) {
   if (target != nullptr) {
       sf::Vector2f targetPosition = target->getPosition();
       sf::Vector2f projectilePosition = getPosition();
       sf::Vector2f direction = targetPosition - projectilePosition;
       double distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
       if (distance > 0) {
           sf::Vector2f velocity = direction / static_cast<float>(distance) * static_cast<float>(speed);
           setPosition(projectilePosition + velocity * static_cast<float>(deltaTime));
       }
       if (distance <= speed * deltaTime) {
           target->takeDamage(damage);
           setTarget(nullptr);
       }
   }
}

void Ship::fireWeapon(Ship* target) {
   if (target != nullptr && weaponCooldown <= 0) {
       Projectile* projectile = createProjectile();
       projectile->setDamage(attackPower);
       projectile->setSpeed(projectileSpeed);
       projectile->setTarget(target);
       projectile->setSource(this);
       projectiles.push_back(projectile);
       weaponCooldown = weaponReloadTime;
   }
}

Projectile* Ship::createProjectile() {
   return new Projectile();
}

void Ship::updateProjectiles(double deltaTime) {
   for (int i = 0; i < projectiles.size(); ++i) {
       Projectile* projectile = projectiles[i];
       projectile->update(deltaTime);
       if (projectile->getTarget() == nullptr) {
           delete projectile;
           projectiles.erase(projectiles.begin() + i);
           --i;
       }
   }
}

void Ship::setProjectileSpeed(double speed) {
   projectileSpeed = speed;
}

double Ship::getProjectileSpeed() const {
   return projectileSpeed;
}

void Ship::setWeaponReloadTime(double time) {
   weaponReloadTime = time;
}

double Ship::getWeaponReloadTime() const {
   return weaponReloadTime;
}

void Ship::setShield(double shield) {
   this->shield = shield;
}

double Ship::getShield() const {
   return shield;
}

void Ship::takeDamage(double damage) {
   double shieldDamage = std::min(damage, shield);
   shield -= shieldDamage;
   double hullDamage = damage - shieldDamage;
   health -= hullDamage;
   if (health <= 0) {
       destroy();
   }
}

void Ship::setHull(double hull) {
   health = hull;
}

double Ship::getHull() const {
   return health;
}

void Ship::destroy() {
   setDestroyed(true);
   setPosition(sf::Vector2f(-1000, -1000));
}

void BattleSystem::setProjectileRadius(double radius) {
   this->projectileRadius = radius;
}

double BattleSystem::getProjectileRadius() const {
   return projectileRadius;
}

void BattleSystem::renderBattleScene() {
   renderPlanets();
   renderShips();
   renderProjectiles();
}

void BattleSystem::renderPlanets() {
   for (Planet* planet : planets) {
       sf::CircleShape planetShape(planet->getRadius());
       planetShape.setFillColor(planet->getColor());
       planetShape.setPosition(planet->getPosition());
       battleWindow.draw(planetShape);
   }
}

void BattleSystem::renderShips() {
   for (Ship* ship : ships) {
       sf::CircleShape shipShape(shipRadius);
       shipShape.setFillColor(ship->getColor());
       shipShape.setPosition(ship->getPosition());
       battleWindow.draw(shipShape);
   }
}

void BattleSystem::renderProjectiles() {
   for (Projectile* projectile : projectiles) {
       sf::CircleShape projectileShape(projectileRadius);
       projectileShape.setFillColor(sf::Color::Red);
       projectileShape.setPosition(projectile->getPosition());
       battleWindow.draw(projectileShape);
   }
}

void BattleSystem::setShipRadius(double radius) {
   shipRadius = radius;
}

double BattleSystem::getShipRadius() const {
   return shipRadius;
}

void BattleSystem::addProjectile(Projectile* projectile) {
   projectiles.push_back(projectile);
}

void BattleSystem::removeProjectile(Projectile* projectile) {
   projectiles.erase(std::remove(projectiles.begin(), projectiles.end(), projectile), projectiles.end());
   delete projectile;
}

void BattleSystem::updateProjectiles(double deltaTime) {
   for (int i = 0; i < projectiles.size(); ++i) {
       Projectile* projectile = projectiles[i];
       projectile->update(deltaTime);
       if (projectile->getTarget() == nullptr) {
           removeProjectile(projectile);
           --i;
       }
   }
}

void BattleSystem::setPlanets(const std::vector<Planet*>& planets) {
   this->planets = planets;
}

void BattleSystem::setShips(const std::vector<Ship*>& ships) {
   this->ships = ships;
}

void BattleSystem::setBattleWindow(sf::RenderWindow& window) {
   battleWindow = window;
}

void AI::analyzeGameState() {
   analyzePlanets();
   analyzeShips();
   analyzeEnemies();
   analyzeResources();
}

void AI::analyzePlanets() {
   for (Planet* planet : observablePlanets) {
       if (planet->getOwner() == aiPlayer->getPlayerNumber()) {
           evaluateOwnPlanet(planet);
       } else {
           evaluateEnemyPlanet(planet);
       }
   }
}

void AI::analyzeShips() {
   for (Ship* ship : observableShips) {
       if (ship->getOwner() == aiPlayer->getPlayerNumber()) {
           evaluateOwnShip(ship);
       } else {
           evaluateEnemyShip(ship);
       }
   }
}

void AI::analyzeEnemies() {
   for (Player* player : observablePlayers) {
       if (player != aiPlayer) {
           evaluateEnemy(player);
       }
   }
}

void AI::analyzeResources() {
   evaluateResources();
}

void AI::evaluateOwnPlanet(Planet* planet) {
   int populationThreshold = 1000;
   int infrastructureThreshold = 50;
   int defenseThreshold = 20;
   if (planet->getPopulation() < populationThreshold) {
       prioritizePlanetDevelopment(planet);
   }
   if (planet->getInfrastructure() < infrastructureThreshold) {
       prioritizePlanetInfrastructure(planet);
   }
   if (planet->getDefenseLevel() < defenseThreshold) {
       prioritizePlanetDefense(planet);
   }
}

void AI::evaluateEnemyPlanet(Planet* planet) {
   int populationThreshold = 2000;
   int defenseThreshold = 30;
   if (planet->getPopulation() > populationThreshold && planet->getDefenseLevel() < defenseThreshold) {
       considerInvasion(planet);
   }
}

void AI::evaluateOwnShip(Ship* ship) {
   int weaponThreshold = 50;
   int shieldThreshold = 100;
   if (ship->getWeaponDamage() < weaponThreshold) {
       prioritizeShipWeaponUpgrade(ship);
   }
   if (ship->getShield() < shieldThreshold) {
       prioritizeShipShieldUpgrade(ship);
   }
}

void AI::evaluateEnemyShip(Ship* ship) {
   int weaponThreshold = 75;
   int shieldThreshold = 150;
   if (ship->getWeaponDamage() > weaponThreshold && ship->getShield() > shieldThreshold) {
       considerEngagement(ship);
   } else {
       considerAvoidance(ship);
   }
}

void AI::evaluateEnemy(Player* player) {
   int relationshipThreshold = 50;
   int militaryStrengthThreshold = 100;
   if (player->getRelationshipScore(aiPlayer) < relationshipThreshold && player->getMilitaryStrength() < militaryStrengthThreshold) {
       considerDiplomaticApproach(player);
   } else {
       considerMilitaryApproach(player);
   }
}

void AI::evaluateResources() {
   int metalThreshold = 5000;
   int energyThreshold = 2500;
   if (aiPlayer->getMetal() < metalThreshold) {
       prioritizeResourceProduction(Metal);
   }
   if (aiPlayer->getEnergy() < energyThreshold) {
       prioritizeResourceProduction(Energy);
   }
}

void AI::prioritizePlanetDevelopment(Planet* planet) {
   planetDevelopmentTargets.push_back(planet);
}

void AI::prioritizePlanetInfrastructure(Planet* planet) {
   planetInfrastructureTargets.push_back(planet);
}

void AI::prioritizePlanetDefense(Planet* planet) {
   planetDefenseTargets.push_back(planet);
}

void AI::considerInvasion(Planet* planet) {
   invasionTargets.push_back(planet);
}

void AI::prioritizeShipWeaponUpgrade(Ship* ship) {
   shipWeaponUpgradeTargets.push_back(ship);
}

void AI::prioritizeShipShieldUpgrade(Ship* ship) {
   shipShieldUpgradeTargets.push_back(ship);
}

void AI::considerEngagement(Ship* ship) {
   engagementTargets.push_back(ship);
}

void AI::considerAvoidance(Ship* ship) {
   avoidanceTargets.push_back(ship);
}

void AI::considerDiplomaticApproach(Player* player) {
   diplomaticTargets.push_back(player);
}

void AI::considerMilitaryApproach(Player* player) {
   militaryTargets.push_back(player);
}

void AI::prioritizeResourceProduction(ResourceType resource) {
   resourceProductionPriorities[resource] += 1;
}

void AI::makeDecisions() {
   decidePlanetaryActions();
   decideShipActions();
   decideEnemyActions();
   decideResourceAllocation();
}

void AI::decidePlanetaryActions() {
   for (Planet* planet : planetDevelopmentTargets) {
       double developmentBudget = calculatePlanetDevelopmentBudget(planet);
       planet->investInPopulationGrowth(developmentBudget * 0.5);
       planet->investInResourceProduction(developmentBudget * 0.3);
       planet->investInResearch(developmentBudget * 0.2);
   }
   for (Planet* planet : planetInfrastructureTargets) {
       double infrastructureBudget = calculatePlanetInfrastructureBudget(planet);
       planet->investInInfrastructure(infrastructureBudget);
   }
   for (Planet* planet : planetDefenseTargets) {
       double defenseBudget = calculatePlanetDefenseBudget(planet);
       planet->investInDefense(defenseBudget);
   }
}

void AI::decideShipActions() {
   for (Ship* ship : shipWeaponUpgradeTargets) {
       double weaponUpgradeBudget = calculateShipWeaponUpgradeBudget(ship);
       ship->upgradeWeapons(weaponUpgradeBudget);
   }
   for (Ship* ship : shipShieldUpgradeTargets) {
       double shieldUpgradeBudget = calculateShipShieldUpgradeBudget(ship);
       ship->upgradeShields(shieldUpgradeBudget);
   }
   for (Ship* ship : engagementTargets) {
       engageEnemy(ship);
   }
   for (Ship* ship : avoidanceTargets) {
       avoidEnemy(ship);
   }
}

void AI::decideEnemyActions() {
   for (Player* player : diplomaticTargets) {
       initiateDiplomacy(player);
   }
   for (Player* player : militaryTargets) {
       engageInCombat(player);
   }
   for (Planet* planet : invasionTargets) {
       invadePlanet(planet);
   }
}

void AI::decideResourceAllocation() {
   double totalResourceBudget = calculateTotalResourceBudget();
   double metalProductionBudget = totalResourceBudget * resourceProductionPriorities[Metal] / getTotalResourcePriority();
   double energyProductionBudget = totalResourceBudget * resourceProductionPriorities[Energy] / getTotalResourcePriority();
   allocateResourceProduction(Metal, metalProductionBudget);
   allocateResourceProduction(Energy, energyProductionBudget);
}

double AI::calculatePlanetDevelopmentBudget(Planet* planet) {
   double baseBudget = 1000.0;
   double populationFactor = planet->getPopulation() / 1000.0;
   double budgetMultiplier = 1.0 + populationFactor;
   return baseBudget * budgetMultiplier;
}

double AI::calculatePlanetInfrastructureBudget(Planet* planet) {
   double baseBudget = 500.0;
   double infrastructureFactor = (50.0 - planet->getInfrastructure()) / 50.0;
   double budgetMultiplier = 1.0 + infrastructureFactor;
   return baseBudget * budgetMultiplier;
}

double AI::calculatePlanetDefenseBudget(Planet* planet) {
   double baseBudget = 750.0;
   double defenseFactor = (30.0 - planet->getDefenseLevel()) / 30.0;
   double budgetMultiplier = 1.0 + defenseFactor;
   return baseBudget * budgetMultiplier;
}

double AI::calculateShipWeaponUpgradeBudget(Ship* ship) {
   double baseBudget = 200.0;
   double weaponFactor = (50.0 - ship->getWeaponDamage()) / 50.0;
   double budgetMultiplier = 1.0 + weaponFactor;
   return baseBudget * budgetMultiplier;
}

double AI::calculateShipShieldUpgradeBudget(Ship* ship) {
   double baseBudget = 300.0;
   double shieldFactor = (100.0 - ship->getShield()) / 100.0;
   double budgetMultiplier = 1.0 + shieldFactor;
   return baseBudget * budgetMultiplier;
}

void AI::engageEnemy(Ship* ship) {
   Ship* target = selectTarget(ship, engagementTargets);
   if (target != nullptr) {
       ship->attackTarget(target);
   }
}

void AI::avoidEnemy(Ship* ship) {
   Ship* target = selectTarget(ship, avoidanceTargets);
   if (target != nullptr) {
       ship->fleeFrom(target);
   }
}

void AI::initiateDiplomacy(Player* player) {
   if (player->getRelationshipScore(aiPlayer) < 30) {
       aiPlayer->proposePeace(player);
   } else if (player->getRelationshipScore(aiPlayer) < 70) {
       aiPlayer->proposeTrade(player);
   } else {
       aiPlayer->proposeAlliance(player);
   }
}

void AI::engageInCombat(Player* player) {
   std::vector<Ship*> enemyShips = player->getOwnedShips();
   for (Ship* ship : aiPlayer->getOwnedShips()) {
       Ship* target = selectTarget(ship, enemyShips);
       if (target != nullptr) {
           ship->attackTarget(target);
       }
   }
}

void AI::invadePlanet(Planet* planet) {
   std::vector<Ship*> invasionFleet;
   for (Ship* ship : aiPlayer->getOwnedShips()) {
       if (ship->canInvadePlanet()) {
           invasionFleet.push_back(ship);
       }
   }
   if (invasionFleet.size() >= 3) {
       for (Ship* ship : invasionFleet) {
           ship->invadePlanet(planet);
       }
   }
}

double AI::calculateTotalResourceBudget() {
   return aiPlayer->getMetal() + aiPlayer->getEnergy();
}

int AI::getTotalResourcePriority() {
   int totalPriority = 0;
   for (const auto& entry : resourceProductionPriorities) {
       totalPriority += entry.second;
   }
   return totalPriority;
}

void AI::allocateResourceProduction(ResourceType resource, double budget) {
   for (Planet* planet : aiPlayer->getOwnedPlanets()) {
       if (resource == Metal) {
           planet->investInMining(budget);
       } else if (resource == Energy) {
           planet->investInEnergyProduction(budget);
       }
   }
}

Ship* AI::selectTarget(Ship* ship, const std::vector<Ship*>& targets) {
   Ship* selectedTarget = nullptr;
   double minDistance = std::numeric_limits<double>::max();
   for (Ship* target : targets) {
       double distance = calculateDistance(ship->getPosition(), target->getPosition());
       if (distance < minDistance) {
           selectedTarget = target;
           minDistance = distance;
       }
   }
   return selectedTarget;
}

double AI::calculateDistance(const sf::Vector2f& position1, const sf::Vector2f& position2) {
   double dx = position2.x - position1.x;
   double dy = position2.y - position1.y;
   return std::sqrt(dx * dx + dy * dy);
}

void AI::executeActions(double deltaTime) {
   executePlanetaryActions(deltaTime);
   executeShipActions(deltaTime);
   executeEnemyActions(deltaTime);
}

void AI::executePlanetaryActions(double deltaTime) {
   for (Planet* planet : planetDevelopmentTargets) {
       planet->update(deltaTime);
   }
   for (Planet* planet : planetInfrastructureTargets) {
       planet->update(deltaTime);
   }
   for (Planet* planet : planetDefenseTargets) {
       planet->update(deltaTime);
   }
}

void AI::executeShipActions(double deltaTime) {
   for (Ship* ship : shipWeaponUpgradeTargets) {
       ship->update(deltaTime);
   }
   for (Ship* ship : shipShieldUpgradeTargets) {
       ship->update(deltaTime);
   }
   for (Ship* ship : engagementTargets) {
       ship->update(deltaTime);
   }
   for (Ship* ship : avoidanceTargets) {
       ship->update(deltaTime);
   }
}

void AI::executeEnemyActions(double deltaTime) {
   for (Planet* planet : invasionTargets) {
       planet->update(deltaTime);
   }
}

void AI::resetTargets() {
   planetDevelopmentTargets.clear();
   planetInfrastructureTargets.clear();
   planetDefenseTargets.clear();
   shipWeaponUpgradeTargets.clear();
   shipShieldUpgradeTargets.clear();
   engagementTargets.clear();
   avoidanceTargets.clear();
   diplomaticTargets.clear();
   militaryTargets.clear();
   invasionTargets.clear();
}

void AI::resetResourceProductionPriorities() {
   resourceProductionPriorities[Metal] = 1;
   resourceProductionPriorities[Energy] = 1;
}

bool Ship::canInvadePlanet() {
   return type == InvasionShip;
}

void Ship::invadePlanet(Planet* planet) {
   if (planet->getOwner() != owner && canInvadePlanet()) {
       double invasionStrength = getInvasionStrength();
       double planetDefense = planet->getDefenseLevel();
       if (invasionStrength > planetDefense) {
           planet->setOwner(owner);
           std::cout << "Planet " << planet->getName() << " has been invaded by player " << owner << std::endl;
       }
   }
}

double Ship::getInvasionStrength() const {
   return attackPower * 2.0;
}

void Ship::attackTarget(Ship* target) {
   if (target != nullptr && target->getOwner() != owner) {
       fireWeapon(target);
   }
}

void Ship::fleeFrom(Ship* target) {
   if (target != nullptr) {
       sf::Vector2f direction = getPosition() - target->getPosition();
       double distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
       if (distance > 0) {
           sf::Vector2f velocity = direction / static_cast<float>(distance) * static_cast<float>(speed);
           setPosition(getPosition() + velocity);
       }
   }
}

void Planet::investInPopulationGrowth(double investment) {
   populationGrowthRate += investment * 0.001;
}

void Planet::investInResourceProduction(double investment) {
   miningEfficiency += investment * 0.01;
   energyEfficiency += investment * 0.01;
}

void Planet::investInResearch(double investment) {
   researchOutput += investment * 0.1;
}

void Planet::investInInfrastructure(double investment) {
   infrastructure += investment * 0.1;
}

void Planet::investInDefense(double investment) {
   defenseLevel += investment * 0.05;
}

void Planet::investInMining(double investment) {
    miningEfficiency += investment * 0.02;
}

void Planet::investInEnergyProduction(double investment) {
   energyEfficiency += investment * 0.02;
}

void Player::updateResearchOutput() {
   double totalResearchOutput = 0.0;
   for (Planet* planet : ownedPlanets) {
       totalResearchOutput += planet->getResearchOutput();
   }
   setResearchOutput(totalResearchOutput);
}

void Game::loadResources() {
   // Load textures
   backgroundTexture.loadFromFile("resources/background.png");
   planetTexture.loadFromFile("resources/planet.png");
   shipTexture.loadFromFile("resources/ship.png");
   // Load fonts
   font.loadFromFile("resources/font.ttf");
   // Load sound effects
   weaponSound.loadFromFile("resources/weapon.wav");
   explosionSound.loadFromFile("resources/explosion.wav");
   // Load music
   backgroundMusic.openFromFile("resources/music.ogg");
}

void Game::playBackgroundMusic() {
   backgroundMusic.setLoop(true);
   backgroundMusic.play();
}

void Game::stopBackgroundMusic() {
   backgroundMusic.stop();
}

void Game::playWeaponSound() {
   weaponSound.play();
}

void Game::playExplosionSound() {
   explosionSound.play();
}

void Game::updateGraphics(double deltaTime) {
   window.clear();
   renderBackground();
   gameState.renderPlanets();
   gameState.renderShips();
   gameState.renderProjectiles();
   renderUI();
   window.display();
}

void Game::renderBackground() {
   sf::Sprite backgroundSprite(backgroundTexture);
   window.draw(backgroundSprite);
}

void Game::renderUI() {
   renderPlayerInfo();
   renderButtonMenu();
   renderMinimap();
}

void Game::renderPlayerInfo() {
   sf::Text playerText;
   playerText.setFont(font);
   playerText.setCharacterSize(18);
   playerText.setFillColor(sf::Color::White);
   playerText.setPosition(10.f, 10.f);
   std::stringstream ss;
   ss << "Player: " << gameState.getCurrentPlayer()->getName() << std::endl;
   ss << "Planets: " << gameState.getCurrentPlayer()->getOwnedPlanets().size() << std::endl;
   ss << "Ships: " << gameState.getCurrentPlayer()->getOwnedShips().size() << std::endl;
   ss << "Metal: " << gameState.getCurrentPlayer()->getMetal() << std::endl;
   ss << "Energy: " << gameState.getCurrentPlayer()->getEnergy() << std::endl;
   playerText.setString(ss.str());
   window.draw(playerText);
}

void Game::renderButtonMenu() {
   sf::RectangleShape buttonShape;
   buttonShape.setSize(sf::Vector2f(100.f, 30.f));
   buttonShape.setFillColor(sf::Color::Red);
   sf::Text buttonText;
   buttonText.setFont(font);
   buttonText.setCharacterSize(18);
   buttonText.setFillColor(sf::Color::White);
   // Render end turn button
   buttonShape.setPosition(800.f, 700.f);
   buttonText.setString("End Turn");
   sf::FloatRect endTurnBounds = buttonText.getLocalBounds();
   buttonText.setOrigin(endTurnBounds.width / 2.f, endTurnBounds.height / 2.f);
   buttonText.setPosition(850.f, 715.f);
   window.draw(buttonShape);
   window.draw(buttonText);
   // Render build ship button  
   buttonShape.setPosition(800.f, 740.f);
   buttonText.setString("Build Ship");
   sf::FloatRect buildShipBounds = buttonText.getLocalBounds();
   buttonText.setOrigin(buildShipBounds.width / 2.f, buildShipBounds.height / 2.f);
   buttonText.setPosition(850.f, 755.f);
   window.draw(buttonShape);
   window.draw(buttonText);
}

void Game::renderMinimap() {
   sf::RectangleShape minimapShape;
   minimapShape.setSize(sf::Vector2f(200.f, 200.f));
   minimapShape.setFillColor(sf::Color(128, 128, 128));
   minimapShape.setPosition(800.f, 500.f);
   window.draw(minimapShape);
   // Render minimap contents...
}

void Game::handleEvents() {
   sf::Event event;
   while (window.pollEvent(event)) {
       if (event.type == sf::Event::Closed) {
           window.close();
       }
       else if (event.type == sf::Event::MouseButtonPressed) {
           handleMouseClick(event.mouseButton);
       }
       else if (event.type == sf::Event::KeyPressed) {
           handleKeyPress(event.key);
       }
   }
}

void Game::handleMouseClick(const sf::Event::MouseButtonEvent& mouseButton) {
   if (mouseButton.button == sf::Mouse::Left) {
       sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
       handleLeftClick(mousePosition);
   }
   else if (mouseButton.button == sf::Mouse::Right) {
       sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
       handleRightClick(mousePosition);
   }
}

void Game::handleKeyPress(const sf::Event::KeyEvent& key) {
   if (key.code == sf::Keyboard::Space) {
       gameState.endTurn();
   }
   else if (key.code == sf::Keyboard::B) {
       gameState.buildShip();
   }
   // Handle other key presses...
}

void Game::handleLeftClick(const sf::Vector2i& position) {
   // Check if end turn button is clicked
   if (position.x >= 800 && position.x <= 900 && position.y >= 700 && position.y <= 730) {
       gameState.endTurn();
   }
   // Check if a planet is clicked
   for (Planet* planet : gameState.getPlanets()) {
       if (planet->containsPoint(position)) {
           gameState.setSelectedPlanet(planet);
           break;
       }
   }
   // Check if a ship is clicked
   for (Ship* ship : gameState.getCurrentPlayer()->getOwnedShips()) {
       if (ship->containsPoint(position)) {
           gameState.setSelectedShip(ship);
           break;
       }
   }
}

void Game::handleRightClick(const sf::Vector2i& position) {
   if (gameState.getSelectedShip() != nullptr) {
       Ship* selectedShip = gameState.getSelectedShip();
       sf::Vector2f targetPosition = window.mapPixelToCoords(position);
       selectedShip->setTargetPosition(targetPosition);
   }
}

bool Planet::containsPoint(const sf::Vector2i& point) const {
   sf::Vector2f planetPosition = getPosition();
   float distance = std::sqrt(std::pow(point.x - planetPosition.x, 2) + std::pow(point.y - planetPosition.y, 2));
   return distance <= getRadius();
}

bool Ship::containsPoint(const sf::Vector2i& point) const {
   sf::Vector2f shipPosition = getPosition();
   float distance = std::sqrt(std::pow(point.x - shipPosition.x, 2) + std::pow(point.y - shipPosition.y, 2));
   return distance <= getRadius();
}

void Ship::setTargetPosition(const sf::Vector2f& position) {
   targetPosition = position;
}

void Ship::moveToTargetPosition(double deltaTime) {
   sf::Vector2f currentPosition = getPosition();
   sf::Vector2f direction = targetPosition - currentPosition;
   float distance = std::sqrt(std::pow(direction.x, 2) + std::pow(direction.y, 2));
   if (distance > 0) {
       sf::Vector2f velocity = direction / distance * getSpeed();
       sf::Vector2f newPosition = currentPosition + velocity * static_cast<float>(deltaTime);
       setPosition(newPosition);
   }
}

void Ship::update(double deltaTime) {
   moveToTargetPosition(deltaTime);
   // Update other ship properties...
}

void GameState::endTurn() {
   currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
   performAIActions();
}

void GameState::performAIActions() {
   for (Player* player : players) {
       if (player != getCurrentPlayer()) {
           AI* ai = player->getAI();
           ai->performActions(*this);
       }
   }
}

void AI::performActions(GameState& gameState) {
   analyzeGameState(gameState);
   makeDecisions();
   executeActions(gameState);
}
void AI::analyzeGameState(const GameState& gameState) {
   // Analyze planets, ships, enemies, resources, etc.
   for (const Planet* planet : gameState.getPlanets()) {
       // Analyze planet properties (e.g., owner, resources, defenses)
       analyzePlanet(planet);
   }
   
   for (const Ship* ship : gameState.getShips()) {
       // Analyze ship properties (e.g., owner, type, position, target)
       analyzeShip(ship);
   }
   
   // Analyze other game state elements (e.g., enemies, resources)
   analyzeEnemies(gameState);
   analyzeResources(gameState);
}

void AI::makeDecisions() {
   // Make decisions based on the analysis
   // Decide on actions for each ship (e.g., move, attack, defend)
   for (Ship* ship : ownedShips) {
       // Determine the best action for the ship based on the analysis
       ShipAction action = decideShipAction(ship);
       
       // Set the ship's target position or other properties based on the decision
       if (action == ShipAction::Move) {
           Planet* targetPlanet = selectTargetPlanet(ship);
           if (targetPlanet) {
               ship->setTargetPosition(targetPlanet->getPosition());
           }
       } else if (action == ShipAction::Attack) {
           Ship* targetShip = selectTargetShip(ship);
           if (targetShip) {
               ship->setTargetPosition(targetShip->getPosition());
               ship->setAttackTarget(targetShip);
           }
       } else if (action == ShipAction::Defend) {
           Planet* planetToDefend = selectPlanetToDefend(ship);
           if (planetToDefend) {
               ship->setTargetPosition(planetToDefend->getPosition());
           }
       }
   }
   
   // Make other decisions (e.g., planet management, resource allocation)
   decidePlanetManagement();
   decideResourceAllocation();
}
void AI::executeActions(GameState& gameState) {
   // Execute actions based on the decisions
   for (Ship* ship : ownedShips) {
       // Move the ship to its target position
       ship->moveToTargetPosition(gameState.getDeltaTime());
       
       // Perform other actions (e.g., attack, defend)
       if (ship->hasAttackTarget()) {
           Ship* targetShip = ship->getAttackTarget();
           ship->attackShip(targetShip, gameState.getDeltaTime());
       }
       
       // Check if the ship needs to defend a planet
       if (ship->isDefending()) {
           Planet* planetToDefend = ship->getDefendingPlanet();
           ship->defendPlanet(planetToDefend, gameState.getDeltaTime());
       }
   }
   
   // Execute other actions (e.g., planet management, resource allocation)
   executePlanetManagement(gameState);
   executeResourceAllocation(gameState);
}

void GameState::setSelectedPlanet(Planet* planet) {
   selectedPlanet = planet;
}

void GameState::setSelectedShip(Ship* ship) {
   selectedShip = ship;
}

Planet* GameState::getSelectedPlanet() const {
   return selectedPlanet;
}

Ship* GameState::getSelectedShip() const {
   return selectedShip;
}

Player* GameState::getCurrentPlayer() const {
   return players[currentPlayerIndex];
}

void Player::setAI(AI* ai) {
   this->ai = ai;
}

AI* Player::getAI() const {
   return ai;
}

void Planet::update(double deltaTime) {
   // Update planet properties, such as population, resources, etc.
   // ...
}

void Projectile::update(double deltaTime) {
   // Update projectile position and check for collisions
   // ...
}

void Projectile::render(sf::RenderWindow& window) {
   sf::CircleShape projectileShape(5.f);
   projectileShape.setFillColor(sf::Color::Red);
   projectileShape.setPosition(position);
   window.draw(projectileShape);
}

void GameState::renderProjectiles() {
   for (Projectile* projectile : projectiles) {
       projectile->render(window);
   }
}

void GameState::addProjectile(Projectile* projectile) {
   projectiles.push_back(projectile);
}

void GameState::removeProjectile(Projectile* projectile) {
   auto it = std::find(projectiles.begin(), projectiles.end(), projectile);
   if (it != projectiles.end()) {
       projectiles.erase(it);
       delete projectile;
   }
}

void GameState::updateProjectiles(double deltaTime) {
   for (Projectile* projectile : projectiles) {
       projectile->update(deltaTime);
   }
}

void Game::run() {
   loadResources();
   playBackgroundMusic();
   while (window.isOpen()) {
       double deltaTime = clock.restart().asSeconds();
       handleEvents();
       gameState.update(deltaTime);
       updateGraphics(deltaTime);
   }
   stopBackgroundMusic();
}

int main() {
   Game game;
   game.run();
   return 0;
}

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include <cmath>
#include <random>
#include <chrono>
#include <fstream>
#include <sstream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <SFML/Audio.hpp>

enum ResourceType {
   Metal,
   Energy
};

class Ship;
class Planet;
class Player;
class Technology;
class GameState;
class AI;

struct Projectile {
   sf::Vector2f position;
   double damage;
   double speed;
   Ship* target;
   Ship* source;

   Projectile() : damage(0.0), speed(0.0), target(nullptr), source(nullptr) {}

   void setDamage(double damage);
   double getDamage() const;
   void setSpeed(double speed);
   double getSpeed() const;
   void setTarget(Ship* target);
   Ship* getTarget() const;
   void setSource(Ship* source);
   Ship* getSource() const;
   void update(double deltaTime);
   void render(sf::RenderWindow& window);
};

struct FleetOrder {
   enum OrderType {
       MOVE_TO,
       ATTACK,
       DEFEND
   };

   OrderType type;
   sf::Vector2f target;
};

class Ship {
private:
   int owner;
   std::string type;
   sf::Vector2f position;
   sf::Vector2f targetPosition;
   double health;
   double shield;
   double attackPower;
   double defenseRating;
   double speed;
   double projectileSpeed;
   double weaponCooldown;
   double weaponReloadTime;
   bool destroyed;
   std::vector<Projectile*> projectiles;

public:
   Ship(const std::string& type);
   std::string getType() const;
   void setOwner(int owner);
   int getOwner() const;
   void setPosition(const sf::Vector2f& position);
   sf::Vector2f getPosition() const;
   void setTargetPosition(const sf::Vector2f& position);
   void moveToTargetPosition(double deltaTime);
   void update(double deltaTime);
   void render(sf::RenderWindow& window);
   void setHealth(double health);
   double getHealth() const;
   void setShield(double shield);
   double getShield() const;
   void setAttackPower(double attackPower);
   double getAttackPower() const;
   void setDefenseRating(double defenseRating);
   double getDefenseRating() const;
   void setSpeed(double speed);
   double getSpeed() const;
   void fireWeapon(Ship* target);
   void setProjectileSpeed(double speed);
   double getProjectileSpeed() const;
   void setWeaponReloadTime(double time);
   double getWeaponReloadTime() const;
   void takeDamage(double damage);
   bool isDestroyed() const;
   void destroy();
   void updateProjectiles(double deltaTime);
   bool canAttack() const;
   void resetWeaponCooldown();
   sf::Color getColor() const;
   bool canInvadePlanet() const;
   void invadePlanet(Planet* planet);
   double getInvasionStrength() const;
   void attackTarget(Ship* target);
   void fleeFrom(Ship* target);
};

class Planet {
private:
   int x;
   int y;
   int owner;
   int population;
   double temperature;
   double gravity;
   double metal;
   double energy;
   double food;
   double infrastructure;
   double defense;
   int terraformingLevel;
   int miningLevel;
   int shipbuildingCapacity;
   int defenseLevel;
   double miningEfficiency;
   double energyEfficiency;
   double populationGrowthRate;
   double researchOutput;

public:
   Planet(int x, int y, int owner, int population, double temperature, double gravity, double metal);
   int getX() const;
   int getY() const;
   int getOwner() const;
   void setOwner(int owner);
   int getPopulation() const;
   void setPopulation(int population);
   double getTemperature() const;
   double getGravity() const;
   double getMetal() const;
   void setMetal(double metal);
   int getTerraformingLevel() const;
   void setTerraformingLevel(int level);
   int getMiningLevel() const;
   void setMiningLevel(int level);
   int getShipbuildingCapacity() const;
   void setShipbuildingCapacity(int capacity);
   int getDefenseLevel() const;
   void setDefenseLevel(int level);
   void increaseMiningEfficiency(double amount);
   void increaseEnergyEfficiency(double amount);
   void upgradeDefenses(double amount);
   void increasePopulationGrowth(double amount);
   double getColonizationCost() const;
   double getRadius() const;
   sf::Vector2f getPosition() const;
   sf::Color getColor() const;
   void update(double deltaTime);
   void render(sf::RenderWindow& window);
   bool containsPoint(const sf::Vector2i& point) const;
   void investInPopulationGrowth(double investment);
   void investInResourceProduction(double investment);
   void investInResearch(double investment);
   void investInInfrastructure(double investment);
   void investInDefense(double investment);
   void investInMining(double investment);
   void investInEnergyProduction(double investment);
};

class Player {
private:
   int playerNumber;
   std::string playerName;
   double temperaturePreference;
   double gravityPreference;
   int totalPopulation;
   double metal;
   double energy;
   double researchOutput;
   std::vector<Planet*> ownedPlanets;
   std::vector<Ship> ownedShips;
   std::vector<Technology*> researchedTechnologies;
   std::vector<Player*> allies;
   std::vector<Player*> enemies;
   double warWeariness;
   int militaryStrength;
   int espionageEffectiveness;
   int counterEspionageEffectiveness;
   std::unordered_map<Player*, int> relationshipScores;
   AI* ai;

public:
   Player(int playerNumber, const std::string& playerName, double temperaturePreference, double gravityPreference);
   void setResources(double metal, double energy);
   double getMetal() const;
   double getEnergy() const;
   void addPlanet(Planet* planet);
   void removePlanet(Planet* planet);
   void addShip(Ship ship);
   void removeShip(const Ship& ship);
   void setResearchOutput(double output);
   double getResearchOutput() const;
   void addTechnology(Technology* technology);
   void handleTradeOfferRejection(Player* sender, const TradeOffer& offer);
   void handleAllianceRejection(Player* sender);
   void handleWarDeclaration(Player* enemy);
   void handlePeaceRejection(Player* enemy);
   bool isEnemy(Player* player) const;
   bool isAtWarWith(Player* player) const;
   int getRelationshipScore(Player* player) const;
   int getWarWeariness() const;
   int getMilitaryStrength() const;
   void proposePeace(Player* player);
   void setName(const std::string& name);
   std::string getName() const;
   int getPlayerNumber() const;
   int getShipCount() const;
   int getPlanetCount() const;
   std::vector<Planet*> getOwnedPlanets() const;
   std::vector<Ship> getOwnedShips() const;
   std::vector<Technology*> getResearchedTechnologies() const;
   void setWarWeariness(int weariness);
   void updateMilitaryStrength(int strength);
   void updateEspionageEffectiveness(int effectiveness);
   int getEspionageEffectiveness() const;
   void setCounterEspionageEffectiveness(int effectiveness);
   int getCounterEspionageEffectiveness() const;
   void conductEspionage(Player* targetPlayer);
   void stealResources(Player* targetPlayer);
   void stealTechnology(Player* targetPlayer);
   void gainIntel(Player* targetPlayer);
   void failEspionage(Player* targetPlayer);
   bool hasTechnology(Technology* technology) const;
   void updateDiplomaticRelations(Player* player, int change);
   void initiateDiplomaticMeeting(Player* player);
   void proposeAlliance(Player* player);
   void proposeTrade(Player* player);
   void declareWar(Player* player);
   void formAlliance(Player* player);
   void conductTrade(Player* player);
   void improveDiplomaticRelations(Player* player);
   int calculateAllianceAcceptanceChance(Player* player);
   int calculateTradeAcceptanceChance(Player* player);
   double calculateTradeAmount(Player* player);
   void updatePlanetUpgrades(Planet* planet);
   void updateShipUpgrades(Ship* ship);
   void updateTechnologyUpgrades(Technology* technology);
   void updateResearchOutput();
   void removeEnemy(Player* enemy);
   void addAlly(Player* ally);
   void removeAlly(Player* ally);
   bool isAlly(Player* player) const;
   void updateRelationshipScore(Player* player, int score);
   void setAI(AI* ai);
   AI* getAI() const;
};

class Technology {
private:
   std::string name;
   int level;
   double researchCost;
   double researchProgress;

public:
   Technology(const std::string& name, int level, double researchCost);
   std::string getName() const;
   int getLevel() const;
   double getResearchCost() const;
   double getResearchProgress() const;
   void setResearchProgress(double progress);
   bool isResearched() const;
   void setResearched(bool researched);
   int getMetalCost() const;
   int getEnergyCost() const;
   void applyEffects(Player* player);
};

struct TradeOffer {
   double metalOffer;
   double energyOffer;
   double metalRequest;
   double energyRequest;
};

class AI {
private:
   Player* aiPlayer;
   std::vector<Planet*> ownedPlanets;
   std::vector<Ship*> ownedShips;
   std::vector<Technology*> availableTechnologies;
   std::vector<Player*> players;
   std::vector<Planet> observablePlanets;
   std::vector<Ship> observableShips;
   std::vector<Player> observablePlayers;
   std::vector<Technology> observableTechnologies;
   std::vector<GameEvent> observableGameEvents;
   std::vector<Planet*> planetDevelopmentTargets;
   std::vector<Planet*> planetInfrastructureTargets;
   std::vector<Planet*> planetDefenseTargets;
   std::vector<Ship*> shipWeaponUpgradeTargets;
   std::vector<Ship*> shipShieldUpgradeTargets;
   std::vector<Ship*> engagementTargets;
   std::vector<Ship*> avoidanceTargets;
   std::vector<Player*> diplomaticTargets;
   std::vector<Player*> militaryTargets;
   std::vector<Planet*> invasionTargets;
   std::unordered_map<ResourceType, int> resourceProductionPriorities;

public:
   AI(Galaxy& galaxy);
   void update(double deltaTime);
   void analyzeGameState(const GameState& gameState);
   void makeDecisions();
   void executeActions(GameState& gameState);
   void decidePlanetaryActions();
   void decideShipActions();
   void decideEnemyActions();
   void decideResourceAllocation();
   double calculatePlanetDevelopmentBudget(Planet* planet);
   double calculatePlanetInfrastructureBudget(Planet* planet);
   double calculatePlanetDefenseBudget(Planet* planet);
   double calculateShipWeaponUpgradeBudget(Ship* ship);
   double calculateShipShieldUpgradeBudget(Ship* ship);
   void engageEnemy(Ship* ship);
   void avoidEnemy(Ship* ship);
   void initiateDiplomacy(Player* player);
   void engageInCombat(Player* player);
   void invadePlanet(Planet* planet);
   double calculateTotalResourceBudget();
   int getTotalResourcePriority() const;
   void allocateResourceProduction(ResourceType resource, double budget);
   Ship* selectTarget(Ship* ship, const std::vector<Ship*>& targets);
   double calculateDistance(const sf::Vector2f& position1, const sf::Vector2f& position2);
   void updateObservableGameState();
   void resetTargets();
   void resetResourceProductionPriorities();
   void evaluateOwnPlanet(Planet* planet);
   void evaluateEnemyPlanet(Planet* planet);
   void evaluateOwnShip(Ship* ship);
   void evaluateEnemyShip(Ship* ship);
   void evaluateEnemy(Player* player);
   void evaluateResources();
   void prioritizePlanetDevelopment(Planet* planet);
   void prioritizePlanetInfrastructure(Planet* planet);
   void prioritizePlanetDefense(Planet* planet);
   void considerInvasion(Planet* planet);
   void prioritizeShipWeaponUpgrade(Ship* ship);
   void prioritizeShipShieldUpgrade(Ship* ship);
   void considerEngagement(Ship* ship);
   void considerAvoidance(Ship* ship);
   void considerDiplomaticApproach(Player* player);
   void considerMilitaryApproach(Player* player);
   void prioritizeResourceProduction(ResourceType resource);
   bool isVisible(const Planet& planet) const;
   bool isVisible(const Ship& ship) const;
   bool isVisible(const Player& player) const;
   bool isVisible(const Technology& technology) const;
   bool isVisible(const GameEvent& event) const;
   void analyzePlanets();
   void analyzeShips();
   void analyzeEnemies();
   void analyzeResources();
};

class GameState {
private:
   std::vector<Planet*> planets;
   std::vector<Player*> players;
   std::vector<Ship*> ships;
   std::vector<Technology*> technologies;
   std::vector<Projectile*> projectiles;
   int currentPlayerIndex;
   Planet* selectedPlanet;
   Ship* selectedShip;
   sf::RenderWindow window;

public:
   std::vector<Planet*> getPlanets() const;
   std::vector<Player*> getPlayers() const;
   Technology* getRandomUnresearchedTechnology();
   void endTurn();
   void performAIActions();
   void setSelectedPlanet(Planet* planet);
   void setSelectedShip(Ship* ship);
   Planet* getSelectedPlanet() const;
   Ship* getSelectedShip() const;
   Player* getCurrentPlayer() const;
   void renderPlanets();
   void renderShips();
   void renderProjectiles();
   void addProjectile(Projectile* projectile);
   void removeProjectile(Projectile* projectile);
   void updateProjectiles(double deltaTime);
   void update(double deltaTime);
};

struct GameEvent {
   bool isRandomEvent;
   bool isStoryEvent;
   bool isDiplomaticEvent;
   bool isNaturalDisaster;
   bool isTechnologicalBreakthrough;
   bool isPirateAttack;
   bool isAllianceFormation;
   bool isTradeAgreement;
   bool isPeaceTreaty;
   std::string eventMessage;
   std::vector<std::string>choices;

   GameEvent();
   void handleEvent();
   void applyEffects();
   std::string getEventType() const;
   std::string getEventMessage() const;
   int getNumChoices() const;
   std::string getChoice(int index) const;
   void applyRandomEffects();
   void applyStoryEffects();
   void applyDiplomaticEffects();
   void applyNaturalDisasterEffects();
   void applyTechnologicalBreakthroughEffects();
   void applyPirateAttackEffects();
   void displayEventMessage();
   void displayEventChoices();
   int getPlayerChoice();
   void applyChoiceEffects(int choice);
   void handleAllianceProposal();
   void handleTradeAgreement();
   void handlePeaceTreaty();
   Player* getProposingPlayer();
   Player* getReceivingPlayer();
   TradeOffer getTradeOffer();
};

class Game {
private:
   GameState gameState;
   sf::RenderWindow window;
   sf::View view;
   sf::Clock clock;
   sf::Font font;
   sf::Texture backgroundTexture;
   sf::Texture planetTexture;
   sf::Texture shipTexture;
   sf::SoundBuffer weaponSoundBuffer;
   sf::SoundBuffer explosionSoundBuffer;
   sf::Sound weaponSound;
   sf::Sound explosionSound;
   sf::Music backgroundMusic;
   bool isPaused;
   bool isGamePaused;

public:
   Game();
   void run();
   void handleEvents();
   void handleMouseClick(const sf::Event::MouseButtonEvent& mouseButton);
   void handleKeyPress(const sf::Event::KeyEvent& key);
   void handleLeftClick(const sf::Vector2i& position);
   void handleRightClick(const sf::Vector2i& position);
   void updateGraphics(double deltaTime);
   void renderBackground();
   void renderUI();
   void renderPlayerInfo();
   void renderButtonMenu();
   void renderMinimap();
   void loadResources();
   void playBackgroundMusic();
   void stopBackgroundMusic();
   void playWeaponSound();
   void playExplosionSound();
   void showPauseMenu();
   void pauseGame();
   void resumeGame();
   void quickSaveGame();
   void quickLoadGame();
};

class BattleSystem {
private:
   Galaxy& gameGalaxy;
   Player* attacker;
   Player* defender;
   Planet* battlePlanet;
   std::vector<Ship*> attackerShips;
   std::vector<Ship*> defenderShips;
   std::vector<Planet*> planets;
   std::vector<Ship*> ships;
   std::vector<Projectile*> projectiles;
   int round;
   double projectileRadius;
   double shipRadius;
   sf::RenderWindow& battleWindow;

public:
   BattleSystem(Galaxy& galaxy);
   void initiateBattle(Player& attacker, Player& defender, Planet& battlePlanet);
   void simulateBattle();
   void displayBattleSummary();
   void performBattleRound();
   void displayRoundSummary();
   void determineBattleOutcome();
   void resolveBattleVictory(Player& victor, Planet& planet);
   void handleLootDistribution(Player& victor, Planet& planet);
   void updatePlanetOwnership(Player& victor, Planet& planet);
   void prepareShipsForBattle(Player& player, std::vector<Ship*>& ships);
   void performShipAction(Ship* ship, std::vector<Ship*>& enemyShips);
   void removeDestroyedShips(std::vector<Ship*>& ships);
   void displayShipStatus(const std::vector<Ship*>& ships);
   void displayShipActions(const std::vector<Ship*>& ships);
   void applyBattleEffects(Player& victor, Planet& planet);
   void awardBattleRewards(Player& victor, Planet& planet);
   Ship* selectTarget(const std::vector<Ship*>& enemyShips);
   bool isBattleOver();
   void setProjectileRadius(double radius);
   double getProjectileRadius() const;
   void renderBattleScene();
   void renderPlanets();
   void renderShips();
   void renderProjectiles();
   void setShipRadius(double radius);
   double getShipRadius() const;
   void addProjectile(Projectile* projectile);
   void removeProjectile(Projectile* projectile);
   void updateProjectiles(double deltaTime);
   void setPlanets(const std::vector<Planet*>& planets);
   void setShips(const std::vector<Ship*>& ships);
   void setBattleWindow(sf::RenderWindow& window);
};

// Implementations

int main() {
   Game game;
   game.run();
   return 0;
}

// Projectile class
void Projectile::setDamage(double damage) {
   this->damage = damage;
}

double Projectile::getDamage() const {
   return damage;
}

void Projectile::setSpeed(double speed) {
   this->speed = speed;
}

double Projectile::getSpeed() const {
   return speed;
}

void Projectile::setTarget(Ship* target) {
   this->target = target;
}

Ship* Projectile::getTarget() const {
   return target;
}

void Projectile::setSource(Ship* source) {
   this->source = source;
}

Ship* Projectile::getSource() const {
   return source;
}

void Projectile::update(double deltaTime) {
   if (target != nullptr) {
       sf::Vector2f targetPosition = target->getPosition();
       sf::Vector2f projectilePosition = position;
       sf::Vector2f direction = targetPosition - projectilePosition;
       double distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
       if (distance > 0) {
           sf::Vector2f velocity = direction / static_cast<float>(distance) * static_cast<float>(speed);
           position += velocity * static_cast<float>(deltaTime);
       }
       if (distance <= speed * deltaTime) {
           target->takeDamage(damage);
           target = nullptr;
       }
   }
}

void Projectile::render(sf::RenderWindow& window) {
   sf::CircleShape shape(5.f);
   shape.setFillColor(sf::Color::Red);
   shape.setPosition(position);
   window.draw(shape);
}

// Ship class
void Ship::setOwner(int owner) {
   this->owner = owner;
}

int Ship::getOwner() const {
   return owner;
}

void Ship::setPosition(const sf::Vector2f& position) {
   this->position = position;
}

sf::Vector2f Ship::getPosition() const {
   return position;
}

void Ship::setTargetPosition(const sf::Vector2f& position) {
   targetPosition = position;
}

void Ship::moveToTargetPosition(double deltaTime) {
   sf::Vector2f direction = targetPosition - position;
   double distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
   if (distance > 0) {
       sf::Vector2f velocity = direction / static_cast<float>(distance) * static_cast<float>(speed);
       position += velocity * static_cast<float>(deltaTime);
   }
}

void Ship::update(double deltaTime) {
   moveToTargetPosition(deltaTime);
   weaponCooldown = std::max(0.0, weaponCooldown - deltaTime);
   updateProjectiles(deltaTime);
}

void Ship::render(sf::RenderWindow& window) {
   sf::CircleShape shape(10.f);
   shape.setFillColor(getColor());
   shape.setPosition(position);
   window.draw(shape);
}

void Ship::setHealth(double health) {
   this->health = health;
}

double Ship::getHealth() const {
   return health;
}

void Ship::setShield(double shield) {
   this->shield = shield;
}

double Ship::getShield() const {
   return shield;
}

void Ship::setAttackPower(double attackPower) {
   this->attackPower = attackPower;
}

double Ship::getAttackPower() const {
   return attackPower;
}

void Ship::setDefenseRating(double defenseRating) {
   this->defenseRating = defenseRating;
}

double Ship::getDefenseRating() const {
   return defenseRating;
}

void Ship::setSpeed(double speed) {
   this->speed = speed;
}

double Ship::getSpeed() const {
   return speed;
}

void Ship::fireWeapon(Ship* target) {
   if (target != nullptr && weaponCooldown <= 0.0) {
       Projectile* projectile = new Projectile();
       projectile->setDamage(attackPower);
       projectile->setSpeed(projectileSpeed);
       projectile->setPosition(position);
       projectile->setTarget(target);
       projectile->setSource(this);
       projectiles.push_back(projectile);
       weaponCooldown = weaponReloadTime;
       playWeaponSound();
   }
}

void Ship::setProjectileSpeed(double speed) {
   projectileSpeed = speed;
}

double Ship::getProjectileSpeed() const {
   return projectileSpeed;
}

void Ship::setWeaponReloadTime(double time) {
   weaponReloadTime = time;
}

double Ship::getWeaponReloadTime() const {
   return weaponReloadTime;
}

void Ship::takeDamage(double damage) {
   double remainingDamage = damage - shield;
   if (remainingDamage > 0) {
       health -= remainingDamage;
       if (health <= 0) {
           destroy();
           playExplosionSound();
       }
   }
}

bool Ship::isDestroyed() const {
   return destroyed;
}

void Ship::destroy() {
   destroyed = true;
}

void Ship::updateProjectiles(double deltaTime) {
   for (auto it = projectiles.begin(); it != projectiles.end();) {
       Projectile* projectile = *it;
       projectile->update(deltaTime);
       if (projectile->getTarget() == nullptr) {
           delete projectile;
           it = projectiles.erase(it);
       }
       else {
           ++it;
       }
   }
}

bool Ship::canAttack() const {
   return weaponCooldown <= 0.0;
}

void Ship::resetWeaponCooldown() {
   weaponCooldown = 0.0;
}

sf::Color Ship::getColor() const {
   switch (owner) {
       case 0: return sf::Color::Blue;
       case 1: return sf::Color::Red;
       case 2: return sf::Color::Green;
       case 3: return sf::Color::Yellow;
       default: return sf::Color::White;
   }
}

bool Ship::canInvadePlanet() const {
   return type == "InvasionShip";
}

void Ship::invadePlanet(Planet* planet) {
   if (canInvadePlanet() && planet->getOwner() != owner) {
       double invasionStrength = getInvasionStrength();
       double planetDefense = planet->getDefenseLevel();
       if (invasionStrength > planetDefense) {
           planet->setOwner(owner);
           planet->setPopulation(planet->getPopulation() / 2);
           planet->setDefenseLevel(planet->getDefenseLevel() / 2);
       }
   }
}

double Ship::getInvasionStrength() const {
   return attackPower;
}

void Ship::attackTarget(Ship* target) {
   if (target != nullptr && target->getOwner() != owner) {
       fireWeapon(target);
   }
}

void Ship::fleeFrom(Ship* target) {
   if (target != nullptr) {
       sf::Vector2f fleeDirection = position - target->getPosition();
       double distance = std::sqrt(fleeDirection.x * fleeDirection.x + fleeDirection.y * fleeDirection.y);
       if (distance > 0) {
           sf::Vector2f velocity = fleeDirection / static_cast<float>(distance) * static_cast<float>(speed);
           position += velocity;
       }
   }
}

// Planet class
int Planet::getX() const {
   return x;
}

int Planet::getY() const {
   return y;
}

int Planet::getOwner() const {
   return owner;
}

void Planet::setOwner(int owner) {
   this->owner = owner;
}

int Planet::getPopulation() const {
   return population;
}

void Planet::setPopulation(int population) {
   this->population = population;
}

double Planet::getTemperature() const {
   return temperature;
}

double Planet::getGravity() const {
   return gravity;
}

double Planet::getMetal() const {
   return metal;
}

void Planet::setMetal(double metal) {
   this->metal = metal;
}

int Planet::getTerraformingLevel() const {
   return terraformingLevel;
}

void Planet::setTerraformingLevel(int level) {
   terraformingLevel = level;
}

int Planet::getMiningLevel() const {
   return miningLevel;
}

void Planet::setMiningLevel(int level) {
   miningLevel = level;
}

int Planet::getShipbuildingCapacity() const {
   return shipbuildingCapacity;
}

void Planet::setShipbuildingCapacity(int capacity) {
   shipbuildingCapacity = capacity;
}

int Planet::getDefenseLevel() const {
   return defenseLevel;
}

void Planet::setDefenseLevel(int level) {
   defenseLevel = level;
}

void Planet::increaseMiningEfficiency(double amount) {
   miningEfficiency += amount;
}

void Planet::increaseEnergyEfficiency(double amount) {
   energyEfficiency += amount;
}

void Planet::upgradeDefenses(double amount) {
   defenseLevel += static_cast<int>(amount);
}

void Planet::increasePopulationGrowth(double amount) {
   populationGrowthRate += amount;
}

double Planet::getColonizationCost() const {
   return population * 2.0;
}

double Planet::getRadius() const {
   return std::sqrt(population) * 2.0;
}

sf::Vector2f Planet::getPosition() const {
   return sf::Vector2f(x, y);
}

sf::Color Planet::getColor() const {
   switch (owner) {
       case 0: return sf::Color::Blue;
       case 1: return sf::Color::Red;
       case 2: return sf::Color::Green;
       case 3: return sf::Color::Yellow;
       default: return sf::Color::White;
   }
}

void Planet::update(double deltaTime) {
   population += static_cast<int>(population * populationGrowthRate * deltaTime);
   metal += miningEfficiency * deltaTime;
   energy += energyEfficiency * deltaTime;
}

void Planet::render(sf::RenderWindow& window) {
   sf::CircleShape shape(getRadius());
   shape.setFillColor(getColor());
   shape.setPosition(x - getRadius(), y - getRadius());
   window.draw(shape);
}

bool Planet::containsPoint(const sf::Vector2i& point) const {
   sf::Vector2f planetPosition(x, y);
   sf::Vector2f pointPosition(point.x, point.y);
   double distance = std::sqrt(std::pow(planetPosition.x - pointPosition.x, 2) + std::pow(planetPosition.y - pointPosition.y, 2));
   return distance <= getRadius();
}

void Planet::investInPopulationG
rowth(double investment) {
   populationGrowthRate += investment * 0.01;
}

void Planet::investInResourceProduction(double investment) {
   miningEfficiency += investment * 0.01;
   energyEfficiency += investment * 0.01;
}

void Planet::investInResearch(double investment) {
   researchOutput += investment * 0.1;
}

void Planet::investInInfrastructure(double investment) {
   infrastructure += investment * 0.1;
}

void Planet::investInDefense(double investment) {
   defenseLevel += static_cast<int>(investment * 0.1);
}

void Planet::investInMining(double investment) {
   miningEfficiency += investment * 0.01;
}

void Planet::investInEnergyProduction(double investment) {
   energyEfficiency += investment * 0.01;
}

// Player class
Player::Player(int playerNumber, const std::string& playerName, double temperaturePreference, double gravityPreference)
   : playerNumber(playerNumber), playerName(playerName), temperaturePreference(temperaturePreference),
     gravityPreference(gravityPreference), totalPopulation(0), metal(0.0), energy(0.0), researchOutput(0.0),
     warWeariness(0), militaryStrength(0), espionageEffectiveness(0), counterEspionageEffectiveness(0), ai(nullptr) {}

void Player::setResources(double metal, double energy) {
   this->metal = metal;
   this->energy = energy;
}

double Player::getMetal() const {
   return metal;
}

double Player::getEnergy() const {
   return energy;
}

void Player::addPlanet(Planet* planet) {
   ownedPlanets.push_back(planet);
}

void Player::removePlanet(Planet* planet) {
   ownedPlanets.erase(std::remove(ownedPlanets.begin(), ownedPlanets.end(), planet), ownedPlanets.end());
}

void Player::addShip(Ship ship) {
   ownedShips.push_back(ship);
}

void Player::removeShip(const Ship& ship) {
   ownedShips.erase(std::remove(ownedShips.begin(), ownedShips.end(), ship), ownedShips.end());
}

void Player::setResearchOutput(double output) {
   researchOutput = output;
}

double Player::getResearchOutput() const {
   return researchOutput;
}

void Player::addTechnology(Technology* technology) {
   researchedTechnologies.push_back(technology);
}
void Player::handleTradeOfferRejection(Player* sender, const TradeOffer& offer) {
   // Handle trade offer rejection
   // You can implement your own logic here
}

void Player::handleAllianceRejection(Player* sender) {
   // Handle alliance rejection
   // You can implement your own logic here
}

void Player::handleWarDeclaration(Player* enemy) {
   // Handle war declaration
   warWeariness += 10; // Increase war weariness when a war is declared
}

void Player::handlePeaceRejection(Player* enemy) {
   // Handle peace rejection
   // You can implement your own logic here
}

bool Player::isEnemy(Player* player) const {
   return std::find(enemies.begin(), enemies.end(), player) != enemies.end();
}

bool Player::isAtWarWith(Player* player) const {
   return isEnemy(player);
}

int Player::getRelationshipScore(Player* player) const {
   auto it = relationshipScores.find(player);
   if (it != relationshipScores.end()) {
       return it->second;
   }
   return 0;
}

int Player::getWarWeariness() const {
   return warWeariness;
}

int Player::getMilitaryStrength() const {
   return militaryStrength;
}

void Player::proposePeace(Player* player) {
   if (isAtWarWith(player)) {
       // Send a peace proposal to the player
       player->handlePeaceProposal(this);
   }
}

void Player::setName(const std::string& name) {
   playerName = name;
}

std::string Player::getName() const {
   return playerName;
}

int Player::getPlayerNumber() const {
   return playerNumber;
}

int Player::getShipCount() const {
   return static_cast<int>(ownedShips.size());
}

int Player::getPlanetCount() const {
   return static_cast<int>(ownedPlanets.size());
}

std::vector<Planet*> Player::getOwnedPlanets() const {
   return ownedPlanets;
}

std::vector<Ship> Player::getOwnedShips() const {
   return ownedShips;
}

std::vector<Technology*> Player::getResearchedTechnologies() const {
   return researchedTechnologies;
}

void Player::setWarWeariness(int weariness) {
   warWeariness = weariness;
}

void Player::updateMilitaryStrength(int strength) {
   militaryStrength = strength;
}

void Player::updateEspionageEffectiveness(int effectiveness) {
   espionageEffectiveness = effectiveness;
}

int Player::getEspionageEffectiveness() const {
   return espionageEffectiveness;
}

void Player::setCounterEspionageEffectiveness(int effectiveness) {
   counterEspionageEffectiveness = effectiveness;
}

int Player::getCounterEspionageEffectiveness() const {
   return counterEspionageEffectiveness;
}

void Player::conductEspionage(Player* targetPlayer) {
   // Conduct espionage on the target player
   // You can implement your own logic here
}

void Player::stealResources(Player* targetPlayer) {
   // Steal resources from the target player
   // You can implement your own logic here
}

void Player::stealTechnology(Player* targetPlayer) {
   // Steal technology from the target player
   // You can implement your own logic here
}

void Player::gainIntel(Player* targetPlayer) {
   // Gain intel about the target player
   // You can implement your own logic here
}

void Player::failEspionage(Player* targetPlayer) {
   // Fail espionage attempt on the target player
   // You can implement your own logic here
}

bool Player::hasTechnology(Technology* technology) const {
   return std::find(researchedTechnologies.begin(), researchedTechnologies.end(), technology) != researchedTechnologies.end();
}

void Player::updateDiplomaticRelations(Player* player, int change) {
   relationshipScores[player] += change;
}

void Player::initiateDiplomaticMeeting(Player* player) {
   std::cout << "Initiating diplomatic meeting with player " << player->getName() << std::endl;
}

void Player::proposeAlliance(Player* player) {
   std::cout << "Proposing alliance to player " << player->getName() << std::endl;
   if (relationshipScores[player] >= 50) {
      std::cout << "Alliance proposed successfully!" << std::endl;
      updateDiplomaticRelations(player, 20);
   } else {
      std::cout << "Cannot propose alliance. Relationship score is too low." << std::endl;
   }
}

void Player::proposeTrade(Player* player) {
   std::cout << "Player " << name << " proposes a trade to Player " << player->getName() << std::endl;
   updateDiplomaticRelations(player, 5);
}

void Player::declareWar(Player* player) {
   std::cout << "Player " << name << " declares war on Player " << player->getName() << std::endl;
   updateDiplomaticRelations(player, -10);
}

void Player::proposeAlliance(Player* player) {
   std::cout << "Proposing alliance to player " << player->getName() << std::endl;
   if (relationshipScores[player] >= 50) {
      std::cout << "Alliance proposed successfully!" << std::endl;
      updateDiplomaticRelations(player, 20);
   } else {
      std::cout << "Cannot propose alliance. Relationship score is too low." << std::endl;
   }
}

void Player::improveDiplomaticRelations(Player* player) {
   std::cout << "Initiating diplomatic meeting with player " << player->getName() << std::endl;
   if (player->acceptDiplomaticOffer()) {
      std::cout << "Diplomatic relations improved successfully!" << std::endl;
      updateDiplomaticRelations(player, 10);
   } else {
      std::cout << "Failed to improve diplomatic relations." << std::endl;
   }
}

// implement your own logic
int Player::calculateAllianceAcceptanceChance(Player* player) {
   int relationshipScore = relationshipScores[player];
   int allianceChance = relationshipScore / 2;
   return allianceChance;
}

int Player::calculateTradeAcceptanceChance(Player* player) {
   int relationshipScore = relationshipScores[player];
   int tradeChance = relationshipScore / 3;
   return tradeChance;
}

double Player::calculateTradeAmount(Player* player) {
   int relationshipScore = relationshipScores[player];
   double tradeAmount = relationshipScore * 100.0;
   return tradeAmount;
}

void Player::updatePlanetUpgrades(Planet* planet) {
   std::cout << "Updating upgrades for planet " << planet->getName() << std::endl;
   planet->increaseResourceProduction(10);
   planet->improveDefenses(20);
}

void Player::updateShipUpgrades(Ship* ship) {
   std::cout << "Updating upgrades for ship " << ship->getName() << std::endl;
   ship->increaseSpeed(10);
   ship->improveWeapons(20);
}

void Player::updateTechnologyUpgrades(Technology* technology) {
   std::cout << "Updating upgrades for technology " << technology->getName() << std::endl;
   technology->unlockNewAbility("Advanced Sensors");
   technology->improveEfficiency(15);
}


void Player::updateResearchOutput() {
   double totalResearchOutput = 0.0;
   for (Planet* planet : ownedPlanets) {
       totalResearchOutput += planet->researchOutput;
   }
   researchOutput = totalResearchOutput;
}

void Player::removeEnemy(Player* enemy) {
   enemies.erase(std::remove(enemies.begin(), enemies.end(), enemy), enemies.end());
}

void Player::addAlly(Player* ally) {
   allies.push_back(ally);
}

void Player::removeAlly(Player* ally) {
   allies.erase(std::remove(allies.begin(), allies.end(), ally), allies.end());
}

bool Player::isAlly(Player* player) const {
   return std::find(allies.begin(), allies.end(), player) != allies.end();
}

void Player::updateRelationshipScore(Player* player, int score) {
   relationshipScores[player] = score;
}

void Player::setAI(AI* ai) {
   this->ai = ai;
}

AI* Player::getAI() const {
   return ai;
}

// Technology class
Technology::Technology(const std::string& name, int level, double researchCost)
   : name(name), level(level), researchCost(researchCost), researchProgress(0.0) {}

std::string Technology::getName() const {
   return name;
}

int Technology::getLevel() const {
   return level;
}

double Technology::getResearchCost() const {
   return researchCost;
}

double Technology::getResearchProgress() const {
   return researchProgress;
}

void Technology::setResearchProgress(double progress) {
   researchProgress = progress;
}

bool Technology::isResearched() const {
   return researchProgress >= researchCost;
}
void Technology::setResearched(bool researched) {
   if (researched) {
      researchProgress = researchCost;
   } else {
      researchProgress = 0.0;
   }
}
int Technology::getMetalCost() const {
   // Return the metal cost based on the technology level
   return level * 100;
}

int Technology::getEnergyCost() const {
   // Return the energy cost based on the technology level
   return level * 50;
}

void Technology::applyEffects(Player* player) {
   // Apply the effects of the technology to the specified player
   // Increase the player's metal and energy production based on the technology level
   player->setMetalProduction(player->getMetalProduction() + level * 10);
   player->setEnergyProduction(player->getEnergyProduction() + level * 5);
}

// Game class
Game::Game() : currentTurn(0), maxTurns(100), isPaused(false), isGameOver(false) {
   // Initialize the game
   // Create players and assign starting resources
   players.push_back(new Player("Player 1"));
   players.push_back(new Player("Player 2"));
   
   for (Player* player : players) {
      player->setMetal(500);
      player->setEnergy(500);
   }
}

void Game::run() {
   loadResources();
   playBackgroundMusic();

   while (window.isOpen()) {
       double deltaTime = clock.restart().asSeconds();

       handleEvents();

       if (!isPaused && !isGamePaused) {
           gameState.update(deltaTime);
           updateGraphics(deltaTime);
       }
   }

   stopBackgroundMusic();
}

void Game::handleEvents() {
   sf::Event event;
   while (window.pollEvent(event)) {
       if (event.type == sf::Event::Closed) {
           window.close();
       }
       else if (event.type == sf::Event::MouseButtonPressed) {
           handleMouseClick(event.mouseButton);
       }
       else if (event.type == sf::Event::KeyPressed) {
           handleKeyPress(event.key);
       }
   }
}

void Game::handleMouseClick(const sf::Event::MouseButtonEvent& mouseButton) {
   if (mouseButton.button == sf::Mouse::Left) {
       sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
       handleLeftClick(mousePosition);
   }
   else if (mouseButton.button == sf::Mouse::Right) {
       sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
       handleRightClick(mousePosition);
   }
}

void Game::handleKeyPress(const sf::Event::KeyEvent& key) {
   if (key.code == sf::Keyboard::Escape) {
       if (isPaused) {
           resumeGame();
       }
       else {
           showPauseMenu();
       }
   }
   else if (key.code == sf::Keyboard::Space) {
       if (isGamePaused) {
           resumeGame();
       }
       else {
           pauseGame();
       }
   }
   else if (key.code == sf::Keyboard::F5) {
       quickSaveGame();
   }
   else if (key.code == sf::Keyboard::F9) {
       quickLoadGame();
   }
}
void Game::handleLeftClick(const sf::Vector2i& position) {
   // TODO: Implement left click handling
   std::cout << "Left click at (" << position.x << ", " << position.y << ")" << std::endl;
}

void Game::handleRightClick(const sf::Vector2i& position) {
   // Handle right mouse click at the specified position
   // You can implement your own logic here
}

void Game::updateGraphics(double deltaTime) {
   window.clear();
   renderBackground();
   gameState.renderPlanets();
   gameState.renderShips();
   gameState.renderProjectiles();
   renderUI();
   window.display();
}

void Game::renderBackground() {
   // Render the game background
   // You can implement your own logic here
   
   // Example background rendering:
   sf::Texture backgroundTexture;
   if (backgroundTexture.loadFromFile("path/to/background/image.png")) {
       sf::Sprite backgroundSprite(backgroundTexture);
       window.draw(backgroundSprite);
   }
}

void Game::renderUI() {
   renderPlayerInfo();
   renderButtonMenu();
   renderMinimap();
}
void Game::renderPlayerInfo() {
   // Render player information
   // You can implement your own logic here
   
   // Example player info rendering:
   sf::Font font;
   if (font.loadFromFile("path/to/font.ttf")) {
       sf::Text playerInfoText;
       playerInfoText.setFont(font);
       playerInfoText.setCharacterSize(24);
       playerInfoText.setFillColor(sf::Color::White);
       playerInfoText.setString("Player: " + gameState.getPlayerName() + "\nScore: " + std::to_string(gameState.getPlayerScore()));
       playerInfoText.setPosition(10, 10);
       window.draw(playerInfoText);
   }
}
void Game::renderButtonMenu() {
   // Render the button menu
   // You can implement your own logic here
   
   // Example button menu rendering:
   sf::Font font;
   if (font.loadFromFile("path/to/font.ttf")) {
       sf::Text buttonText;
       buttonText.setFont(font);
       buttonText.setCharacterSize(20);
       buttonText.setFillColor(sf::Color::White);
       
       // Render "Build" button
       sf::RectangleShape buildButton(sf::Vector2f(100, 40));
       buildButton.setFillColor(sf::Color(0, 100, 0)); // Dark green
       buildButton.setPosition(10, 100);
       buttonText.setString("Build");
       buttonText.setPosition(buildButton.getPosition() + sf::Vector2f(10, 10));
       window.draw(buildButton);
       window.draw(buttonText);
       
       // Render "Research" button
       sf::RectangleShape researchButton(sf::Vector2f(100, 40));
       researchButton.setFillColor(sf::Color(0, 0, 100)); // Dark blue
       researchButton.setPosition(10, 150);
       buttonText.setString("Research");
       buttonText.setPosition(researchButton.getPosition() + sf::Vector2f(10, 10));
       window.draw(researchButton);
       window.draw(buttonText);
       
       // Render "Diplomacy" button
       sf::RectangleShape diplomacyButton(sf::Vector2f(100, 40));
       diplomacyButton.setFillColor(sf::Color(100, 0, 0)); // Dark red
       diplomacyButton.setPosition(10, 200);
       buttonText.setString("Diplomacy");
       buttonText.setPosition(diplomacyButton.getPosition() + sf::Vector2f(10, 10));
       window.draw(diplomacyButton);
       window.draw(buttonText);
   }
}

void Game::renderMinimap() {
   // Render the minimap
   // You can implement your own logic here
   
   // Example minimap rendering:
   sf::RectangleShape minimapBackground(sf::Vector2f(200, 200));
   minimapBackground.setFillColor(sf::Color(0, 0, 0, 128));
   minimapBackground.setPosition(window.getSize().x - 210, 10);
   window.draw(minimapBackground);
   
   // Render planets on the minimap
   for (const auto& planet : gameState.getPlanets()) {
       sf::CircleShape planetShape(3);
       planetShape.setFillColor(sf::Color::White);
       sf::Vector2f minimapPosition = planet.getPosition() / gameState.getMapSize() * 200.f;
       planetShape.setPosition(window.getSize().x - 210 + minimapPosition.x, 10 + minimapPosition.y);
       window.draw(planetShape);
   }
   
   // Render ships on the minimap
   for (const auto& ship : gameState.getShips()) {
       sf::RectangleShape shipShape(sf::Vector2f(2, 2));
       shipShape.setFillColor(sf::Color::Green);
       sf::Vector2f minimapPosition = ship.getPosition() / gameState.getMapSize() * 200.f;
       shipShape.setPosition(window.getSize().x - 210 + minimapPosition.x, 10 + minimapPosition.y);
       window.draw(shipShape);
   }
}

void Game::loadResources() {
   // Load game resources (textures, fonts, sounds, music)
   // You can implement your own logic here
   
   // Load textures
   if (!planetTexture.loadFromFile("resources/planet_texture.png")) {
       // Error handling
   }
   
   if (!shipTexture.loadFromFile("resources/ship_texture.png")) {
       // Error handling
   }
   
   // Load fonts
   if (!font.loadFromFile("resources/font.ttf")) {
       // Error handling
   }
   
   // Load sounds
   if (!buttonClickSound.loadFromFile("resources/button_click.wav")) {
       // Error handling
   }
   
   // Load music
   if (!backgroundMusic.openFromFile("resources/background_music.ogg")) {
       // Error handling
   }
}

void Game::playBackgroundMusic() {
   // Play the background music
   if (!backgroundMusic.openFromFile("path/to/background/music.ogg")) {
       // Error handling: background music file not found
       std::cout << "Error: Background music file not found!" << std::endl;
       return;
   }
   backgroundMusic.setLoop(true);
   backgroundMusic.play();
}

void Game::stopBackgroundMusic() {
   // Stop the background music
   backgroundMusic.stop();
}

void Game::playWeaponSound() {
   // Play the weapon sound effect
   if (!weaponSound.openFromFile("path/to/weapon/sound.wav")) {
       // Error handling: weapon sound file not found
       std::cout << "Error: Weapon sound file not found!" << std::endl;
       return;
   }
   weaponSound.play();
}

void Game::playExplosionSound() {
   // Play the explosion sound effect
   if (!explosionSound.openFromFile("path/to/explosion/sound.wav")) {
       // Error handling: explosion sound file not found
       std::cout << "Error: Explosion sound file not found!" << std::endl;
       return;
   }
   explosionSound.play();
}

void Game::showPauseMenu() {
   isPaused = true;
   // Show the pause menu
   // Create a semi-transparent background rectangle
   sf::RectangleShape backgroundShape(sf::Vector2f(window.getSize().x, window.getSize().y));
   backgroundShape.setFillColor(sf::Color(0, 0, 0, 128));
   window.draw(backgroundShape);
   
   // Create a pause menu text
   sf::Font font;
   if (font.loadFromFile("path/to/font.ttf")) {
       sf::Text pauseText;
       pauseText.setFont(font);
       pauseText.setCharacterSize(48);
       pauseText.setFillColor(sf::Color::White);
       pauseText.setString("Paused");
       pauseText.setPosition(window.getSize().x / 2 - pauseText.getGlobalBounds().width / 2,
                             window.getSize().y / 2 - pauseText.getGlobalBounds().height / 2);
       window.draw(pauseText);
   }
}

void Game::pauseGame() {
   isGamePaused = true;
}

void Game::resumeGame() {
   isPaused = false;
   isGamePaused = false;
}


void Game::quickSaveGame() {
   // Quick save the game
   saveGameState("quicksave.dat");
}

void Game::quickLoadGame() {
   // Quick load the game
   loadGameState("quicksave.dat");
}

// GameState class
std::vector<Planet*> GameState::getPlanets() const {
   return planets;
}

std::vector<Player*> GameState::getPlayers() const {
   return players;
}

Technology* GameState::getRandomUnresearchedTechnology() {
   std::vector<Technology*> unresearchedTechnologies;
   for (Technology* technology : technologies) {
       if (!technology->isResearched()) {
           unresearchedTechnologies.push_back(technology);
       }
   }

   if (!unresearchedTechnologies.empty()) {
       int randomIndex = rand() % unresearchedTechnologies.size();
       return unresearchedTechnologies[randomIndex];
   }

   return nullptr;
}

void GameState::endTurn() {
   currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
   performAIActions();
}

void GameState::performAIActions() {
   for (Player* player : players) {
       if (player != getCurrentPlayer()) {
           AI* ai = player->getAI();
           ai->performActions(*this);
       }
   }
}

void GameState::setSelectedPlanet(Planet* planet) {
   selectedPlanet = planet;
}

void GameState::setSelectedShip(Ship* ship) {
   selectedShip = ship;
}

Planet* GameState::getSelectedPlanet() const {
   return selectedPlanet;
}

Ship* GameState::getSelectedShip() const {
   return selectedShip;
}

Player* GameState::getCurrentPlayer() const {
   return players[currentPlayerIndex];
}

void GameState::renderPlanets() {
   for (Planet* planet : planets) {
       planet->render(window);
   }
}

void GameState::renderShips() {
   for (Player* player : players) {
       for (const Ship& ship : player->getOwnedShips()) {
           ship.render(window);
       }
   }
}

void GameState::renderProjectiles() {
   for (Projectile* projectile : projectiles) {
       projectile->render(window);
   }
}

void GameState::addProjectile(Projectile* projectile) {
   projectiles.push_back(projectile);
}

void GameState::removeProjectile(Projectile* projectile) {
   projectiles.erase(std::remove(projectiles.begin(), projectiles.end(), projectile), projectiles.end());
   delete projectile;
}

void GameState::updateProjectiles(double deltaTime) {
   for (Projectile* projectile : projectiles) {
       projectile->update(deltaTime);
   }
}

void GameState::update(double deltaTime) {
   for (Planet* planet : planets) {
       planet->update(deltaTime);
   }

   for (Player* player : players) {
       for (Ship& ship : player->getOwnedShips()) {
           ship.update(deltaTime);
       }
   }

   updateProjectiles(deltaTime);
}

// GameEvent class
GameEvent::GameEvent()
   : isRandomEvent(false), isStoryEvent(false), isDiplomaticEvent(false),
     isNaturalDisaster(false), isTechnologicalBreakthrough(false),
     isPirateAttack(false), isAllianceFormation(false), isTradeAgreement(false),
     isPeaceTreaty(false) {}

void GameEvent::handleEvent() {
   displayEventMessage();
   applyEffects();

   if (isStoryEvent) {
       displayEventChoices();
       int choice = getPlayerChoice();
       applyChoiceEffects(choice);
   }
   else if (isDiplomaticEvent) {
       if (isAllianceFormation) {
           handleAllianceProposal();
       }
       else if (isTradeAgreement) {
           handleTradeAgreement();
       }
       else if (isPeaceTreaty) {
           handlePeaceTreaty();
       }
   }
}

std::string GameEvent::getEventType() const {
   if (isRandomEvent) {
       if (isNaturalDisaster) {
           return "Natural Disaster";
       }
       else if (isTechnologicalBreakthrough) {
           return "Technological Breakthrough";
       }
       else if (isPirateAttack) {
           return "Pirate Attack";
       }
   }
   else if (isStoryEvent) {
       return "Story Event";
   }
   else if (isDiplomaticEvent) {
       if (isAllianceFormation) {
           return "Alliance Formation";
       }
       else if (isTradeAgreement) {
           return "Trade Agreement";
       }
       else if (isPeaceTreaty) {
           return "Peace Treaty";
       }
   }

   return "Unknown Event";
}

std::string GameEvent::getEventMessage() const {
   return eventMessage;
}

int GameEvent::getNumChoices() const {
   return static_cast<int>(choices.size());
}

std::string GameEvent::getChoice(int index) const {
   if (index >= 0 && index < getNumChoices()) {
       return choices[index];
   }
   return "";
}

void GameEvent::applyRandomEffects() {
   if (isNaturalDisaster) {
       applyNaturalDisasterEffects();
   }
   else if (isTechnologicalBreakthrough) {
       applyTechnologicalBreakthroughEffects();
   }
   else if (isPirateAttack) {
       applyPirateAttackEffects();
   }
}

void GameEvent::applyStoryEffects() {
   // Apply story event effects based on the event type and choices
   if (eventType == "Story Event") {
       if (choices.size() > 0) {
           std::string selectedChoice = choices[0]; // Assume the first choice is selected
           
           if (selectedChoice == "Choice 1") {
               // Apply effects for Choice 1
           }
           else if (selectedChoice == "Choice 2") {
               // Apply effects for Choice 2
           }
           // Add more conditions for other choices
       }
   }
}

void GameEvent::applyDiplomaticEffects() {
   if (isAllianceFormation) {
       // Apply alliance formation effects
       // You can implement your own logic here
   }
   else if (isTradeAgreement) {
       // Apply trade agreement effects
       // You can implement your own logic here
   }
   else if (isPeaceTreaty) {
       // Apply peace treaty effects
       // You can implement your own logic here
   }
}

void GameEvent::applyNaturalDisasterEffects() {
   // Apply natural disaster effects to planets, ships, or players
   // Reduce population and infrastructure on affected planets
   for (auto& planet : affectedPlanets) {
       planet->reducePopulation(disasterSeverity);
       planet->damageInfrastructure(disasterSeverity);
   }
   // Damage or destroy ships in the affected area
   for (auto& ship : affectedShips) {
       ship->takeDamage(disasterSeverity);
   }
}

void GameEvent::applyTechnologicalBreakthroughEffects() {
   // Apply technological breakthrough effects to players or technologies
   // Increase research points for the discovering player
   discoveringPlayer->addResearchPoints(breakthroughResearchPoints);
   // Unlock new technologies or improvements
   discoveringPlayer->unlockTechnology(breakthroughTechnology);
}

void GameEvent::applyPirateAttackEffects() {
   // Apply pirate attack effects to players, ships, or planets
   // Damage or destroy ships in the affected area
   for (auto& ship : affectedShips) {
       ship->takeDamage(pirateAttackStrength);
   }
   // Steal resources from affected planets
   for (auto& planet : affectedPlanets) {
       planet->loseResources(pirateAttackStrength);
   }
   // Reduce reputation of the attacked player
   attackedPlayer->reduceReputation(pirateAttackReputation);
}

void GameEvent::displayEventMessage() {
   std::cout << "Event: " << getEventType() << std::endl;
   std::cout << getEventMessage() << std::endl;
}

void GameEvent::displayEventChoices() {
   std::cout << "Choices:" << std::endl;
   for (int i = 0; i < getNumChoices(); ++i) {
       std::cout << i + 1 << ". " << getChoice(i) << std::endl;
   }
}

int GameEvent::getPlayerChoice() {
   int choice;
   std::cin >> choice;
   return choice;
}
void GameEvent::applyChoiceEffects(int choice) {
   // Apply the effects based on the player's choice
   switch (choice) {
       case 1:
           // Handle choice 1 effects
           break;
       case 2:
           // Handle choice 2 effects
           break;
       // Add more cases for additional choices
       default:
           // Handle invalid choice
           break;
   }
}


void GameEvent::handleAllianceProposal() {
   // Handle alliance proposal event
   displayEventMessage();
   displayEventChoices();
   int choice = getPlayerChoice();
   
   switch (choice) {
       case 1:
           // Accept alliance proposal
           proposingPlayer->formAlliance(receivingPlayer);
           receivingPlayer->formAlliance(proposingPlayer);
           break;
       case 2:
           // Reject alliance proposal
           // No action needed
           break;
       default:
           // Handle invalid choice
           break;
   }
}

void GameEvent::handleTradeAgreement() {
   // Handle trade agreement event
   displayEventMessage();
   displayEventChoices();
   int choice = getPlayerChoice();
   
   switch (choice) {
       case 1:
           // Accept trade agreement
           proposingPlayer->establishTradeAgreement(receivingPlayer);
           receivingPlayer->establishTradeAgreement(proposingPlayer);
           break;
       case 2:
           // Reject trade agreement
           // No action needed
           break;
       default:
           // Handle invalid choice
           break;
   }
   
   applyChoiceEffects(choice);
}

void GameEvent::handlePeaceTreaty() {
   // Handle peace treaty event
   displayEventMessage();
   displayEventChoices();
   int choice = getPlayerChoice();
   
   switch (choice) {
       case 1:
           // Accept peace treaty
           proposingPlayer->signPeaceTreaty(receivingPlayer);
           receivingPlayer->signPeaceTreaty(proposingPlayer);
           break;
       case 2:
           // Reject peace treaty
           // No action needed
           break;
       default:
           // Handle invalid choice
           break;
   }
   
   applyChoiceEffects(choice);
}

Player* GameEvent::getProposingPlayer() {
   // Get the player proposing the event
   return proposingPlayer;
}

Player* GameEvent::getReceivingPlayer() {
   // Get the player receiving the event
   return receivingPlayer;
}

TradeOffer GameEvent::getTradeOffer() {
   // Get the trade offer associated with the event
   return tradeOffer;
}

// BattleSystem class
BattleSystem::BattleSystem(Galaxy& galaxy)
   : gameGalaxy(galaxy) {}

void BattleSystem::initiateBattle(Player& attacker, Player& defender, Planet& battlePlanet) {
   this->attacker = &attacker;
   this->defender = &defender;
   this->battlePlanet = &battlePlanet;

   attackerShips.clear();
   defenderShips.clear();

   for (const Ship& ship : attacker.getOwnedShips()) {
       attackerShips.push_back(const_cast<Ship*>(&ship));
   }

   for (const Ship& ship : defender.getOwnedShips()) {
       defenderShips.push_back(const_cast<Ship*>(&ship));
   }

   round = 1;
}

void BattleSystem::simulateBattle() {
   while (!isBattleOver()) {
       performBattleRound();
       displayRoundSummary();
       ++round;
   }

   determineBattleOutcome();
}

void BattleSystem::displayBattleSummary() {
   std::cout << "Battle Summary:" << std::endl;
   std::cout << "Attacker: " << attacker->getName() << std::endl;
   std::cout << "Defender: " << defender->getName() << std::endl;
   std::cout << "Battle Planet: " << battlePlanet->getX() << ", " << battlePlanet->getY() << std::endl;
   std::cout << "Rounds: " << round << std::endl;
   std::cout << "Outcome: ";

   if (attackerShips.empty() && defenderShips.empty()) {
       std::cout << "Draw" << std::endl;
   }
   else if (attackerShips.empty()) {
       std::cout << "Defender Victory" << std::endl;
   }
   else if (defenderShips.empty()) {
       std::cout << "Attacker Victory" << std::endl;
   }
   else {
       std::cout << "Ongoing" << std::endl;
   }
}

void BattleSystem::performBattleRound() {
   for (Ship* ship : attackerShips) {
       Ship* target = selectTarget(defenderShips);
       if (target != nullptr) {
           ship->attackTarget(target);
       }
   }

   for (Ship* ship : defenderShips) {
       Ship* target = selectTarget(attackerShips);
       if (target != nullptr) {
           ship->attackTarget(target);
       }
   }

   removeDestroyedShips(attackerShips);
   removeDestroyedShips(defenderShips);
}

void BattleSystem::displayRoundSummary() {
   std::cout << "Round " << round << " Summary:" << std::endl;
   std::cout << "Attacker Ships: " << attackerShips.size() << std::endl;
   std::cout << "Defender Ships: " << defenderShips.size() << std::endl;
}

void BattleSystem::determineBattleOutcome() {
   if (attackerShips.empty() && defenderShips.empty()) {
       // Draw
   }
   else if (attackerShips.empty()) {
       // Defender victory
       resolveBattleVictory(*defender, *battlePlanet);
   }
   else if (defenderShips.empty()) {
       // Attacker victory
       resolveBattleVictory(*attacker, *battlePlanet);
   }
}

void BattleSystem::resolveBattleVictory(Player& victor, Planet& planet) {
   planet.setOwner(victor.getPlayerNumber());
   applyBattleEffects(victor, planet);
}

void BattleSystem::handleLootDistribution(Player& victor, Planet& planet) {
   double metalLoot = planet.getMetal() * 0.1;
   victor.setResources(victor.getMetal() + metalLoot, victor.getEnergy());
   planet.setMetal(planet.getMetal() - metalLoot);
}

void BattleSystem::updatePlanetOwnership(Player& victor, Planet& planet) {
   planet.setOwner(victor.getPlayerNumber());
}

void BattleSystem::prepareShipsForBattle(Player& player, std::vector<Ship*>& ships) {
   for (const Ship& ship : player.getOwnedShips()) {
       ships.push_back(const_cast<Ship*>(&ship));
   }
}

void BattleSystem::performShipAction(Ship* ship, std::vector<Ship*>& enemyShips) {
   Ship* target = selectTarget(enemyShips);
   if (target != nullptr) {
       ship->attackTarget(target);
   }
}

void BattleSystem::removeDestroyedShips(std::vector<Ship*>& ships) {
   ships.erase(std::remove_if(ships.begin(), ships.end(),
                              [](const Ship* ship) { return ship->isDestroyed(); }),
               ships.end());
}

void BattleSystem::displayShipStatus(const std::vector<Ship*>& ships) {
   for (const Ship* ship : ships) {
       std::cout << "Ship: " << ship->getType() << ", Health: " << ship->getHealth() << std::endl;
   }
}

void BattleSystem::displayShipActions(const std::vector<Ship*>& ships) {
   for (const Ship* ship : ships) {
       std::cout << "Ship: " << ship->getType() << ", Action: Attack" << std::endl;
   }
}

void BattleSystem::applyBattleEffects(Player& victor, Planet& planet) {
   handleLootDistribution(victor, planet);
   updatePlanetOwnership(victor, planet);
}

void BattleSystem::awardBattleRewards(Player& victor, Planet& planet) {
   handleLootDistribution(victor, planet);
   updatePlanetOwnership(victor, planet);
}

Ship* BattleSystem::selectTarget(const std::vector<Ship*>& enemyShips) {
   if (!enemyShips.empty()) {
       int randomIndex = rand() % enemyShips.size();
       return enemyShips[randomIndex];
   }
   return nullptr;
}

bool BattleSystem::isBattleOver() {
   return attackerShips.empty() || defenderShips.empty();
}

void BattleSystem::setProjectileRadius(double radius) {
   projectileRadius = radius;
}

double BattleSystem::getProjectileRadius() const {
   return projectileRadius;
}

void BattleSystem::renderBattleScene() {
   renderPlanets();
   renderShips();
   renderProjectiles();
}

void BattleSystem::renderPlanets() {
   for (Planet* planet : planets) {
       planet->render(battleWindow);
   }
}

void BattleSystem::renderShips() {
   for (Ship* ship : ships) {
       ship->render(battleWindow);
   }
}

void BattleSystem::renderProjectiles() {
   for (Projectile* projectile : projectiles) {
       projectile->render(battleWindow);
   }
}

void BattleSystem::setShipRadius(double radius) {
   shipRadius = radius;
}

double BattleSystem::getShipRadius() const {
   return shipRadius;
}

void BattleSystem::addProjectile(Projectile* projectile) {
   projectiles.push_back(projectile);
}

void BattleSystem::removeProjectile(Projectile* projectile) {
   projectiles.erase(std::remove(projectiles.begin(), projectiles.end(), projectile), projectiles.end());
   delete projectile;
}

void BattleSystem::updateProjectiles(double deltaTime) {
   for (Projectile* projectile : projectiles) {
       projectile->update(deltaTime);
   }
}

void BattleSystem::setPlanets(const std::vector<Planet*>& planets) {
   this->planets = planets;
}

void BattleSystem::setShips(const std::vector<Ship*>& ships) {
   this->ships = ships;
}

void BattleSystem::setBattleWindow(sf::RenderWindow& window) {
   battleWindow = window;
}

// AI class
void AI::analyzeGameState(const GameState& gameState) {
   observablePlanets = gameState.getPlanets();
   observableShips.clear();
   observablePlayers = gameState.getPlayers();
   observableTechnologies.clear();
   observableGameEvents.clear();

   for (Player* player : observablePlayers) {
       if (player != aiPlayer) {
           for (const Ship& ship : player->getOwnedShips()) {
               observableShips.push_back(ship);
           }
           for (Technology* technology : player->getResearchedTechnologies()) {
               observableTechnologies.push_back(*technology);
           }
       }
   }

   analyzePlanets();
   analyzeShips();
   analyzeEnemies();
   analyzeResources();
}

void AI::makeDecisions() {
   decidePlanetaryActions();
   decideShipActions();
   decideEnemyActions();
   decideResourceAllocation();
}

void AI::executeActions(GameState& gameState) {
   executePlanetaryActions(gameState);
   executeShipActions(gameState);
   executeEnemyActions(gameState);
}

void AI::decidePlanetaryActions() {
   for (Planet* planet : observablePlanets) {
       if (planet->getOwner() == aiPlayer->getPlayerNumber()) {
           if (planet->getPopulation() < 1000) {
               prioritizePlanetDevelopment(planet);
           }
           if (planet->getDefenseLevel() < 50) {
               prioritizePlanetDefense(planet);
           }
       }
       else {
           if (planet->getPopulation() > 2000 && planet->getDefenseLevel() < 100) {
               considerInvasion(planet);
           }
       }
   }
}

void AI::decideShipActions() {
   for (const Ship& ship : observableShips) {
       if (ship.getOwner() == aiPlayer->getPlayerNumber()) {
           if (ship.getWeaponDamage() < 50) {
               prioritizeShipWeaponUpgrade(&ship);
           }
           if (ship.getShield() < 100) {
               prioritizeShipShieldUpgrade(&ship);
           }
       }
       else {
           if (ship.getWeaponDamage() > 75 && ship.getShield() > 150) {
               considerEngagement(&ship);
           }
           else {
               considerAvoidance(&ship);
           }
       }
   }
}

void AI::decideEnemyActions() {
   for (Player* player : observablePlayers) {
       if (player != aiPlayer) {
           if (player->getMilitaryStrength() < 500 && player->getRelationshipScore(aiPlayer) < 50) {
               considerDiplomaticApproach(player);
           }
           else {
               considerMilitaryApproach(player);
           }
       }
   }
}

void AI::decideResourceAllocation() {
   double totalBudget = aiPlayer->getMetal() + aiPlayer->getEnergy();
   double metalAllocation = totalBudget * 0.6;
   double energyAllocation = totalBudget - metalAllocation;

   allocateResourceProduction(Metal, metalAllocation);
   allocateResourceProduction(Energy, energyAllocation);

   aiPlayer->setResources(aiPlayer->getMetal() - metalAllocation, aiPlayer->getEnergy() - energyAllocation);
}

double AI::calculatePlanetDevelopmentBudget(Planet* planet) {
   double budget = planet->getPopulation() * 0.1;
   return budget;
}

double AI::calculatePlanetInfrastructureBudget(Planet* planet) {
   double budget = planet->getPopulation() * 0.05;
   return budget;
}

double AI::calculatePlanetDefenseBudget(Planet* planet) {
   double budget = planet->getPopulation() * 0.02;
   return budget;
}

double AI::calculateShipWeaponUpgradeBudget(Ship* ship) {
   double budget = ship->getWeaponDamage() * 0.2;
   return budget;
}

double AI::calculateShipShieldUpgradeBudget(Ship* ship) {
   double budget = ship->getShield() * 0.1;
   return budget;
}

void AI::engageEnemy(Ship* ship) {
   Ship* target = selectTarget(ship, engagementTargets);
   if (target != nullptr) {
       ship->attackTarget(target);
   }
}

void AI::avoidEnemy(Ship* ship) {
   Ship* closestShip = nullptr;
   double closestDistance = std::numeric_limits<double>::max();

   for (Ship* target : avoidanceTargets) {
       double distance = calculateDistance(ship->getPosition(), target->getPosition());
       if (distance < closestDistance) {
           closestShip = target;
           closestDistance = distance;
       }
   }

   if (closestShip != nullptr) {
       ship->fleeFrom(closestShip);
   }
}

void AI::initiateDiplomacy(Player* player) {
   int relationshipScore = aiPlayer->getRelationshipScore(player);
   if (relationshipScore < 30) {
       aiPlayer->proposePeace(player);
   }
   else if (relationshipScore < 70) {
       aiPlayer->proposeTrade(player);
   }
   else {
       aiPlayer->proposeAlliance(player);
   }
}

void AI::engageInCombat(Player* player) {
   for (Ship& ship : aiPlayer->getOwnedShips()) {
       Ship* target = selectTarget(&ship, player->getOwnedShips());
       if (target != nullptr) {
           ship.attackTarget(target);
       }
   }
}

void AI::invadePlanet(Planet* planet) {
   std::vector<Ship*> invadingShips;
   for (Ship& ship : aiPlayer->getOwnedShips()) {
       if (ship.canInvadePlanet()) {
           invadingShips.push_back(&ship);
       }
   }

   if (invadingShips.size() >= planet->getDefenseLevel() * 0.5) {
       for (Ship* ship : invadingShips) {
           ship->invadePlanet(planet);
       }
   }
}

double AI::calculateTotalResourceBudget() {
   return aiPlayer->getMetal() + aiPlayer->getEnergy();
}

int AI::getTotalResourcePriority() const {
   int totalPriority = 0;
   for (const auto& priority : resourceProductionPriorities) {
       totalPriority += priority.second;
   }
   return totalPriority;
}

void AI::allocateResourceProduction(ResourceType resource, double budget) {
   for (Planet* planet : ownedPlanets) {
       double allocation = budget * resourceProductionPriorities[resource] / getTotalResourcePriority();
       if (resource == Metal) {
           planet->investInMining(allocation);
       }
       else if (resource == Energy) {
           planet->investInEnergyProduction(allocation);
       }
   }
}

Ship* AI::selectTarget(Ship* ship, const std::vector<Ship>& targets) {
   double minDistance = std::numeric_limits<double>::max();
   Ship* selectedTarget = nullptr;

   for (const Ship& target : targets) {
       double distance = calculateDistance(ship->getPosition(), target.getPosition());
       if (distance < minDistance) {
           minDistance = distance;
           selectedTarget = const_cast<Ship*>(&target);
       }
   }

   return selectedTarget;
}

double AI::calculateDistance(const sf::Vector2f& position1, const sf::Vector2f& position2) {
   double dx = position2.x - position1.x;
   double dy = position2.y - position1.y;
   return std::sqrt(dx * dx + dy * dy);
}

void AI::updateObservableGameState() {
   observablePlanets.clear();
   observableShips.clear();
   observablePlayers.clear();
   observableTechnologies.clear();
   observableGameEvents.clear();
}

void AI::resetTargets() {
   planetDevelopmentTargets.clear();
   planetInfrastructureTargets.clear();
   planetDefenseTargets.clear();
   shipWeaponUpgradeTargets.clear();
   shipShieldUpgradeTargets.clear();
   engagementTargets.clear();
   avoidanceTargets.clear();
   diplomaticTargets.clear();
   militaryTargets.clear();
   invasionTargets.clear();
}

void AI::resetResourceProductionPriorities() {
   resourceProductionPriorities.clear();
   resourceProductionPriorities[Metal] = 1;
   resourceProductionPriorities[Energy] = 1;
}

void AI::evaluateOwnPlanet(Planet* planet) {
   if (planet->getPopulation() < 1000) {
       prioritizePlanetDevelopment(planet);
   }
   if (planet->getDefenseLevel() < 50) {
       prioritizePlanetDefense(planet);
   }
}

void AI::evaluateEnemyPlanet(Planet* planet) {
   if (planet->getPopulation() > 2000 && planet->getDefenseLevel() < 100) {
       considerInvasion(planet);
   }
}

void AI::evaluateOwnShip(Ship* ship) {
   if (ship->getWeaponDamage() < 50) {
       prioritizeShipWeaponUpgrade(ship);
   }
   if (ship->getShield() < 100) {
       prioritizeShipShieldUpgrade(ship);
   }
}

void AI::evaluateEnemyShip(Ship* ship) {
   if (ship->getWeaponDamage() > 75 && ship->getShield() > 150) {
       considerEngagement(ship);
   }
   else {
       considerAvoidance(ship);
   }
}

void AI::evaluateEnemy(Player* player) {
   if (player->getMilitaryStrength() < 500 && player->getRelationshipScore(aiPlayer) < 50) {
       considerDiplomaticApproach(player);
   }
   else {
       considerMilitaryApproach(player);
   }
}

void AI::evaluateResources() {
   double metalThreshold = 5000.0;
   double energyThreshold = 2500.0;

   if (aiPlayer->getMetal() < metalThreshold) {
       prioritizeResourceProduction(Metal);
   }
   if (aiPlayer->getEnergy() < energyThreshold) {
       prioritizeResourceProduction(Energy);
   }
}

void AI::prioritizePlanetDevelopment(Planet* planet) {
   planetDevelopmentTargets.push_back(planet);
}

void AI::prioritizePlanetDefense(Planet* planet) {
   planetDefenseTargets.push_back(planet);
}

void AI::considerInvasion(Planet* planet) {
   invasionTargets.push_back(planet);
}

void AI::prioritizeShipWeaponUpgrade(Ship* ship) {
   shipWeaponUpgradeTargets.push_back(ship);
}

void AI::prioritizeShipShieldUpgrade(Ship* ship) {
   shipShieldUpgradeTargets.push_back(ship);
}

void AI::considerEngagement(Ship* ship) {
   engagementTargets.push_back(ship);
}

void AI::considerAvoidance(Ship* ship) {
   avoidanceTargets.push_back(ship);
}

void AI::considerDiplomaticApproach(Player* player) {
   diplomaticTargets.push_back(player);
}

void AI::considerMilitaryApproach(Player* player) {
   militaryTargets.push_back(player);
}

void AI::prioritizeResourceProduction(ResourceType resource) {
   resourceProductionPriorities[resource] += 1;
}

bool AI::isVisible(const Planet& planet) const {
   return true;
}

bool AI::isVisible(const Ship& ship) const {
   return true;
}

bool AI::isVisible(const Player& player) const {
   return true;
}

bool AI::isVisible(const Technology& technology) const {
   return true;
}

bool AI::isVisible(const GameEvent& event) const {
   return true;
}

void AI::analyzePlanets() {
   for (Planet* planet : observablePlanets) {
       if (planet->getOwner() == aiPlayer->getPlayerNumber()) {
           evaluateOwnPlanet(planet);
       }
       else {
           evaluateEnemyPlanet(planet);
       }
   }
}

void AI::analyzeShips() {
   for (const Ship& ship : observableShips) {
       if (ship.getOwner() == aiPlayer->getPlayerNumber()) {
           evaluateOwnShip(const_cast<Ship*>(&ship));
       }
       else {
           evaluateEnemyShip(const_cast<Ship*>(&ship));
       }
   }
}

void AI::analyzeEnemies() {
   for (Player* player : observablePlayers) {
       if (player != aiPlayer) {
           evaluateEnemy(player);
       }
   }
}

void AI::analyzeResources() {
   evaluateResources();
}

void AI::executePlanetaryActions(GameState& gameState) {
   for (Planet* planet : planetDevelopmentTargets) {
       double budget = calculatePlanetDevelopmentBudget(planet);
       planet->investInPopulationGrowth(budget * 0.5);
       planet->investInResourceProduction(budget * 0.3);
       planet->investInResearch(budget * 0.2);
   }
   for (Planet* planet : planetDefenseTargets) {
       double budget = calculatePlanetDefenseBudget(planet);
       planet->investInDefense(budget);
   }
}

void AI::executeShipActions(GameState& gameState) {
   for (Ship* ship : shipWeaponUpgradeTargets) {
       double budget = calculateShipWeaponUpgradeBudget(ship);
       ship->upgradeWeapons(budget);
   }
   for (Ship* ship : shipShieldUpgradeTargets) {
       double budget = calculateShipShieldUpgradeBudget(ship);
       ship->upgradeShields(budget);
   }
   for (Ship* ship : engagementTargets) {
       engageEnemy(ship);
   }
   for (Ship* ship : avoidanceTargets) {
       avoidEnemy(ship);
   }
}

void AI::executeEnemyActions(GameState& gameState) {
   for (Player* player : diplomaticTargets) {
       initiateDiplomacy(player);
   }
   for (Player* player : militaryTargets) {
       engageInCombat(player);
   }
   for (Planet* planet : invasionTargets) {
       invadePlanet(planet);
   }
}

void AI::performActions(GameState& gameState) {
   resetTargets();
   resetResourceProductionPriorities();
   analyzeGameState(gameState);
   makeDecisions();
   executeActions(gameState);
}

// main.cpp
#include "Game.h"

int main() {
    Game game;
    game.run();
    return 0;
}

// Game.h
#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "GameState.h"
#include "Player.h"
#include "AI.h"

class Game {
private:
    GameState gameState;
    sf::RenderWindow window;
    sf::View view;
    sf::Clock clock;
    bool isPaused;
    bool isGameOver;

public:
    Game();
    void run();

private:
    void processInput();
    void update(double deltaTime);
    void render();
    void loadResources();
    void handleEvents();
};

#endif

// Game.cpp
#include "Game.h"

Game::Game() : isPaused(false), isGameOver(false) {
    // Initialize the game window and view
    window.create(sf::VideoMode(1024, 768), "Spaceward Ho!");
    view = window.getDefaultView();
}

void Game::run() {
    loadResources();

    while (window.isOpen()) {
        double deltaTime = clock.restart().asSeconds();

        processInput();

        if (!isPaused && !isGameOver) {
            update(deltaTime);
        }

        render();
    }
}

void Game::processInput() {
    handleEvents();
}

void Game::update(double deltaTime) {
    gameState.update(deltaTime);
}

void Game::render() {
    window.clear();

    // Render game objects
    gameState.render(window);

    window.display();
}
void Game::loadResources() {
    // Load game resources (textures, fonts, sounds)
    // Placeholder implementation
}

void Game::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        else if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) {
                isPaused = !isPaused;
            }
        }
    }
}

// GameState.h
#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <vector>
#include "Planet.h"
#include "Ship.h"
#include "Player.h"
#include "Technology.h"
#include "Projectile.h"

class GameState {
private:
    std::vector<Planet> planets;
    std::vector<Player> players;
    std::vector<Ship> ships;
    std::vector<Technology> technologies;
    std::vector<Projectile> projectiles;

public:
    void update(double deltaTime);
    void render(sf::RenderWindow& window);

    std::vector<Planet>& getPlanets();
    std::vector<Player>& getPlayers();
    std::vector<Ship>& getShips();
    std::vector<Technology>& getTechnologies();
    std::vector<Projectile>& getProjectiles();
};

#endif

// GameState.cpp
#include "GameState.h"

void GameState::update(double deltaTime) {
    for (Planet& planet : planets) {
        planet.update(deltaTime);
    }

    for (Player& player : players) {
        player.update(deltaTime);
    }

    for (Ship& ship : ships) {
        ship.update(deltaTime);
    }

    for (Technology& technology : technologies) {
        technology.update(deltaTime);
    }

    for (Projectile& projectile : projectiles) {
        projectile.update(deltaTime);
    }
}

void GameState::render(sf::RenderWindow& window) {
    for (Planet& planet : planets) {
        planet.render(window);
    }

    for (Ship& ship : ships) {
        ship.render(window);
    }

    for (Projectile& projectile : projectiles) {
        projectile.render(window);
    }
}

std::vector<Planet>& GameState::getPlanets() {
    return planets;
}

std::vector<Player>& GameState::getPlayers() {
    return players;
}

std::vector<Ship>& GameState::getShips() {
    return ships;
}

std::vector<Technology>& GameState::getTechnologies() {
    return technologies;
}

std::vector<Projectile>& GameState::getProjectiles() {
    return projectiles;
}

// Planet.h
#ifndef PLANET_H
#define PLANET_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

class Planet {
private:
    int x;
    int y;
    int owner;
    int population;
    double temperature;
    double gravity;
    double metal;
    int defenseLevel;
    // Add other planet properties

public:
    Planet(int x, int y, int owner, int population, double temperature, double gravity, double metal);

    void update(double deltaTime);
    void render(sf::RenderWindow& window);

    int getX() const;
    int getY() const;
    int getOwner() const;
    int getPopulation() const;
    double getTemperature() const;
    double getGravity() const;
    double getMetal() const;
    int getDefenseLevel() const;
    // Add other getter methods

    void setOwner(int owner);
    void setPopulation(int population);
    void setMetal(double metal);
    void setDefenseLevel(int level);
    // Add other setter methods

    void investInPopulationGrowth(double investment);
    void investInResourceProduction(double investment);
    void investInResearch(double investment);
    void investInDefense(double investment);
    // Add other investment methods
};

#endif

// Planet.cpp
#include "Planet.h"

Planet::Planet(int x, int y, int owner, int population, double temperature, double gravity, double metal)
    : x(x), y(y), owner(owner), population(population), temperature(temperature),
      gravity(gravity), metal(metal), defenseLevel(0) {}

void Planet::update(double deltaTime) {
    // Update planet properties based on investments and time passed
    population += populationGrowthRate * deltaTime;
    metal += resourceProductionRate * deltaTime;
    // Update other properties based on investments and time
}

void Planet::render(sf::RenderWindow& window) {
    // Render planet graphics
    sf::CircleShape planetShape(10.0f);
    planetShape.setFillColor(sf::Color::Blue);
    planetShape.setPosition(x, y);
    window.draw(planetShape);
}

int Planet::getX() const {
    return x;
}

int Planet::getY() const {
    return y;
}

int Planet::getOwner() const {
    return owner;
}

int Planet::getPopulation() const {
    return population;
}

double Planet::getTemperature() const {
    return temperature;
}

double Planet::getGravity() const {
    return gravity;
}

double Planet::getMetal() const {
    return metal;
}

int Planet::getDefenseLevel() const {
    return defenseLevel;
}

void Planet::setOwner(int owner) {
    this->owner = owner;
}

void Planet::setPopulation(int population) {
    this->population = population;
}

void Planet::setMetal(double metal) {
    this->metal = metal;
}

void Planet::setDefenseLevel(int level) {
    defenseLevel = level;
}

void Planet::investInPopulationGrowth(double investment) {
    // Increase population growth based on investment
    populationGrowthRate += investment * populationGrowthInvestmentFactor;
}

void Planet::investInResourceProduction(double investment) {
    // Increase resource production based on investment
    resourceProductionRate += investment * resourceProductionInvestmentFactor;
}

void Planet::investInResearch(double investment) {
    // Increase research output based on investment
    researchOutputRate += investment * researchInvestmentFactor;
}

void Planet::investInDefense(double investment) {
    // Increase defense level based on investment
    defenseLevel += static_cast<int>(investment * defenseInvestmentFactor);
}

// Ship.h
#ifndef SHIP_H
#define SHIP_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

class Ship {
private:
    int owner;
    sf::Vector2f position;
    double health;
    double shield;
    double weaponDamage;
    double speed;
    // Add other ship properties

public:
    Ship(int owner, const sf::Vector2f& position);

    void update(double deltaTime);
    void render(sf::RenderWindow& window);

    int getOwner() const;
    sf::Vector2f getPosition() const;
    double getHealth() const;
    double getShield() const;
    double getWeaponDamage() const;
    double getSpeed() const;
    // Add other getter methods

    void setPosition(const sf::Vector2f& position);
    void takeDamage(double damage);
    void upgradeWeapons(double upgrade);
    void upgradeShields(double upgrade);
    void upgradeSpeed(double upgrade);
    // Add other setter and upgrade methods

    void attackTarget(Ship* target);
    void fleeFrom(Ship* target);
    bool canInvadePlanet() const;
    void invadePlanet(Planet* planet);
    // Add other ship actions
};

#endif

// Ship.cpp
#include "Ship.h"

Ship::Ship(int owner, const sf::Vector2f& position)
    : owner(owner), position(position), health(100.0), shield(0.0), weaponDamage(10.0) {}

void Ship::update(double deltaTime) {
    // Update ship position based on velocity
    position += velocity * deltaTime;

    // Update ship health and shield regeneration
    if (health < maxHealth) {
        health = std::min(health + healthRegenRate * deltaTime, maxHealth);
    }
    if (shield < maxShield) {
        shield = std::min(shield + shieldRegenRate * deltaTime, maxShield);
    }

    // Update ship weapon cooldown
    if (weaponCooldown > 0.0) {
        weaponCooldown = std::max(weaponCooldown - deltaTime, 0.0);
    }

    // Update other ship properties and behavior
}

void Ship::render(sf::RenderWindow& window) {
    // Render ship graphics
    sf::CircleShape shipShape(10.0f);
    shipShape.setFillColor(sf::Color::White);
    shipShape.setPosition(position);
    window.draw(shipShape);
}

int Ship::getOwner() const {
    return owner;
}

sf::Vector2f Ship::getPosition() const {
    return position;
}

double Ship::getHealth() const {
    return health;
}

double Ship::getShield() const {
    return shield;
}

double Ship::getWeaponDamage() const {
    return weaponDamage;
}

void Ship::setPosition(const sf::Vector2f& position) {
    this->position = position;
}

void Ship::takeDamage(double damage) {
    if (shield > 0.0) {
        double remainingDamage = damage - shield;
        shield -= damage;
        if (shield < 0.0) {
            shield = 0.0;
        }
        if (remainingDamage > 0.0) {
            health -= remainingDamage;
        }
    } else {
        health -= damage;
    }
    if (health < 0.0) {
        health = 0.0;
    }
}

void Ship::upgradeWeapons(double upgrade) {
    weaponDamage += upgrade;
}

void Ship::upgradeShields(double upgrade) {
    shield += upgrade;
}

void Ship::attackTarget(Ship* target) {
    double damage = weaponDamage - target->getShield();
    if (damage > 0) {
        target->takeDamage(damage);
    }
}

void Ship::fleeFrom(Ship* target) {
    sf::Vector2f direction = position - target->getPosition();
    direction = direction / std::sqrt(direction.x * direction.x + direction.y * direction.y);
    position += direction * fleeSpeed;
}

bool Ship::canInvadePlanet() const {
    return health > 50.0;
}

void Ship::invadePlanet(Planet* planet) {
    if (canInvadePlanet()) {
        planet->reduceDefense(weaponDamage);
        planet->reduceResources(invasionDamage);
        conqueredPlanets.push_back(planet);
    }
}

// Player.h
#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include "Planet.h"
#include "Ship.h"
#include "Technology.h"

class Player {
private:
    int playerNumber;
    std::string playerName;
    double metal;
    double energy;
    std::vector<Planet*> ownedPlanets;
    std::vector<Ship> ownedShips;
    std::vector<Technology*> researchedTechnologies;
    // Add other player properties

public:
    Player(int playerNumber, const std::string& playerName);

    void update(double deltaTime);

    int getPlayerNumber() const;
    std::string getPlayerName() const;
    double getMetal() const;
    double getEnergy() const;
    const std::vector<Planet*>& getOwnedPlanets() const;
    const std::vector<Ship>& getOwnedShips() const;
    const std::vector<Technology*>& getResearchedTechnologies() const;
    // Add other getter methods

    void setMetal(double metal);
    void setEnergy(double energy);
    void addPlanet(Planet* planet);
    void addShip(const Ship& ship);
    void addTechnology(Technology* technology);
    // Add other setter methods

    void proposePeace(Player* player);
    void proposeTrade(Player* player);
    void proposeAlliance(Player* player);
    // Add other player actions
};

#endif

// Player.cpp
#include "Player.h"
Player::Player(int playerNumber, const std::string& playerName)
    : playerNumber(playerNumber), playerName(playerName), metal(0.0), energy(0.0) {}

void Player::update(double deltaTime) {
    // Update player properties and behavior
    for (Planet* planet : ownedPlanets) {
        planet->update(deltaTime);
    }

    for (Ship& ship : ownedShips) {
        ship.update(deltaTime);
    }

    for (Technology* technology : researchedTechnologies) {
        technology->update(deltaTime);
    }
}

int Player::getPlayerNumber() const {
    return playerNumber;
}

std::string Player::getPlayerName() const {
    return playerName;
}

double Player::getMetal() const {
    return metal;
}

double Player::getEnergy() const {
    return energy;
}

const std::vector<Planet*>& Player::getOwnedPlanets() const {
    return ownedPlanets;
}

const std::vector<Ship>& Player::getOwnedShips() const {
    return ownedShips;
}

const std::vector<Technology*>& Player::getResearchedTechnologies() const {
    return researchedTechnologies;
}


void Player::setMetal(double metal) {
    this->metal = metal;
}

void Player::setEnergy(double energy) {
    this->energy = energy;
}

void Player::addPlanet(Planet* planet) {
    ownedPlanets.push_back(planet);
}

void Player::addShip(const Ship& ship) {
    ownedShips.push_back(ship);
}

void Player::addTechnology(Technology* technology) {
    researchedTechnologies.push_back(technology);
}

void Player::proposePeace(Player* player) {
    // Propose peace to the target player
}

void Player::proposeTrade(Player* player) {
    // Propose trade to the target player
}

void Player::proposeAlliance(Player* player) {
    // Propose alliance to the target player
}

// Technology.h
#ifndef TECHNOLOGY_H
#define TECHNOLOGY_H

#include <string>

class Technology {
private:
    std::string name;
    int level;
    double researchCost;
    // Add other technology properties

public:
    Technology(const std::string& name, int level, double researchCost);

    void update(double deltaTime);

    std::string getName() const;
    int getLevel() const;
    double getResearchCost() const;
    // Add other getter methods

    void research(double investment);
    // Add other technology methods
};

#endif

// Technology.cpp
#include "Technology.h"

Technology::Technology(const std::string& name, int level, double researchCost)
    : name(name), level(level), researchCost(researchCost) {}

void Technology::update(double deltaTime) {
    // Update technology properties and effects based on the elapsed time
    // Increase the technology level based on the research progress
    // Apply the effects of the technology to the game state
}

std::string Technology::getName() const {
    return name;
}

int Technology::getLevel() const {
   return level;
}

double Technology::getResearchCost() const {
   return researchCost;
}

void Technology::research(double investment) {
    // Increase research progress based on investment
    researchCost -= investment;
    if (researchCost <= 0) {
        level++;
        researchCost = getNextLevelCost();
    }
}

// Projectile.h
#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

class Ship;

class Projectile {
private:
   sf::Vector2f position;
   sf::Vector2f velocity;
   double damage;
   Ship* source;
   Ship* target;
   // Add other projectile properties

public:
   Projectile(const sf::Vector2f& position, const sf::Vector2f& velocity, double damage, Ship* source, Ship* target);

   void update(double deltaTime);
   void render(sf::RenderWindow& window);

   sf::Vector2f getPosition() const;
   double getDamage() const;
   Ship* getSource() const;
   Ship* getTarget() const;
   // Add other getter methods
};

#endif

// Projectile.cpp
#include "Projectile.h"
#include "Ship.h"

Projectile::Projectile(const sf::Vector2f& position, const sf::Vector2f& velocity, double damage, Ship* source, Ship* target)
   : position(position), velocity(velocity), damage(damage), source(source), target(target) {}

void Projectile::update(double deltaTime) {
   // Update projectile position based on velocity
   position += velocity * static_cast<float>(deltaTime);

   // Check if the projectile hits the target ship
   if (target != nullptr && getDistance(position, target->getPosition()) <= 5.0f) {
       target->takeDamage(damage);
       target = nullptr;
   }
}

void Projectile::render(sf::RenderWindow& window) {
   sf::CircleShape projectileShape(5.0f);
   projectileShape.setFillColor(sf::Color::Red);
   projectileShape.setPosition(position);
   window.draw(projectileShape);
}

sf::Vector2f Projectile::getPosition() const {
   return position;
}

double Projectile::getDamage() const {
   return damage;
}

Ship* Projectile::getSource() const {
   return source;
}

Ship* Projectile::getTarget() const {
   return target;
}

// AI.h
#ifndef AI_H
#define AI_H

#include <vector>
#include "Player.h"
#include "Planet.h"
#include "Ship.h"
#include "Technology.h"
#include "GameState.h"

class AI {
private:
   Player* aiPlayer;
   std::vector<Planet*> ownedPlanets;
   std::vector<Ship*> ownedShips;
   std::vector<Technology*> availableTechnologies;
   std::vector<Player*> players;
   // Add other AI properties and data structures

public:
   AI(Player* player);

   void performActions(GameState& gameState);

private:
   void analyzeGameState(const GameState& gameState);
   void makeDecisions();
   void executeActions(GameState& gameState);

   void decidePlanetaryActions();
   void decideShipActions();
   void decideEnemyActions();
   void decideResourceAllocation();

   double calculatePlanetDevelopmentBudget(Planet* planet);
   double calculatePlanetInfrastructureBudget(Planet* planet);
   double calculatePlanetDefenseBudget(Planet* planet);
   double calculateShipWeaponUpgradeBudget(Ship* ship);
   double calculateShipShieldUpgradeBudget(Ship* ship);

   void engageEnemy(Ship* ship);
   void avoidEnemy(Ship* ship);
   void initiateDiplomacy(Player* player);
   void engageInCombat(Player* player);
   void invadePlanet(Planet* planet);

   double calculateTotalResourceBudget();
   void allocateResourceProduction(ResourceType resource, double budget);
   Ship* selectTarget(Ship* ship, const std::vector<Ship*>& targets);
   double calculateDistance(const sf::Vector2f& position1, const sf::Vector2f& position2);
};

#endif

// AI.cpp
#include "AI.h"

AI::AI(Player* player) : aiPlayer(player) {}

void AI::performActions(GameState& gameState) {
   ownedPlanets = aiPlayer->getOwnedPlanets();
   ownedShips = aiPlayer->getOwnedShips();
   availableTechnologies = aiPlayer->getResearchedTechnologies();
   players = gameState.getPlayers();

   analyzeGameState(gameState);
   makeDecisions();
   executeActions(gameState);
}
void AI::analyzeGameState(const GameState& gameState) {
   // Analyze the current game state
   // Gather information about owned planets, ships, available technologies, and other players
   ownedPlanets = aiPlayer->getOwnedPlanets();
   ownedShips = aiPlayer->getOwnedShips();
   availableTechnologies = aiPlayer->getResearchedTechnologies();
   players = gameState.getPlayers();
}

void AI::makeDecisions() {
   // Make decisions based on the analysis
   decidePlanetaryActions();
   decideShipActions();
   decideEnemyActions();
   decideResourceAllocation();
}

void AI::executeActions(GameState& gameState) {
   // Execute actions based on the decisions
   // Implement actions for planetary development, ship actions, enemy interactions, and resource allocation
   for (Planet* planet : ownedPlanets) {
      double developmentBudget = calculatePlanetDevelopmentBudget(planet);
      double infrastructureBudget = calculatePlanetInfrastructureBudget(planet);
      double defenseBudget = calculatePlanetDefenseBudget(planet);
      // Allocate resources and perform actions based on the calculated budgets
      allocateResourceProduction(ResourceType::Development, developmentBudget);
      allocateResourceProduction(ResourceType::Infrastructure, infrastructureBudget);
      allocateResourceProduction(ResourceType::Defense, defenseBudget);
   }

   for (Ship* ship : ownedShips) {
      double weaponUpgradeBudget = calculateShipWeaponUpgradeBudget(ship);
      double shieldUpgradeBudget = calculateShipShieldUpgradeBudget(ship);
      // Upgrade ship weapons and shields based on the calculated budgets
      upgradeShipWeapons(ship, weaponUpgradeBudget);
      upgradeShipShields(ship, shieldUpgradeBudget);

      // Engage or avoid enemy ships based on ship capabilities and enemy strength
      const std::vector<Ship*>& enemyShips = gameState.getEnemyShips();
      Ship* target = selectTarget(ship, enemyShips);
      if (target) {
         engageEnemy(ship);
      } else {
         avoidEnemy(ship);
      }
   }

   // Initiate diplomacy or engage in combat with enemy players based on decisions
   for (Player* player : players) {
      if (player != aiPlayer) {
         if (shouldInitiateDiplomacy(player)) {
            initiateDiplomacy(player);
         } else if (shouldEngageInCombat(player)) {
            engageInCombat(player);
         }
      }
   }

   // Invade enemy planets if deemed necessary
   for (Planet* planet : gameState.getEnemyPlanets()) {
      if (shouldInvadePlanet(planet)) {
         invadePlanet(planet);
      }
   }
}

void AI::decidePlanetaryActions() {
   // Decide actions for owned planets
   for (Planet* planet : ownedPlanets) {
      double developmentBudget = calculatePlanetDevelopmentBudget(planet);
      double infrastructureBudget = calculatePlanetInfrastructureBudget(planet);
      double defenseBudget = calculatePlanetDefenseBudget(planet);
      // Allocate resources and perform actions based on the calculated budgets
      allocateResourceProduction(ResourceType::Development, developmentBudget);
      allocateResourceProduction(ResourceType::Infrastructure, infrastructureBudget);
      allocateResourceProduction(ResourceType::Defense, defenseBudget);
   }
}

void AI::decideShipActions() {
   // Decide actions for owned ships
   for (Ship* ship : ownedShips) {
      double weaponUpgradeBudget = calculateShipWeaponUpgradeBudget(ship);
      double shieldUpgradeBudget = calculateShipShieldUpgradeBudget(ship);
      // Upgrade ship weapons and shields based on the calculated budgets
      upgradeShipWeapons(ship, weaponUpgradeBudget);
      upgradeShipShields(ship, shieldUpgradeBudget);

      // Engage or avoid enemy ships based on ship capabilities and enemy strength
      const std::vector<Ship*>& enemyShips = gameState.getEnemyShips();
      Ship* target = selectTarget(ship, enemyShips);
      if (target) {
         engageEnemy(ship, target);
      } else {
         avoidEnemy(ship);
      }
   }
}

void AI::decideEnemyActions() {
   // Decide actions related to enemy players
   for (Player* player : players) {
      if (player != aiPlayer) {
         // Analyze enemy player's strength, owned planets, and ships
         analyzeEnemyStrength(player);
         analyzeEnemyPlanets(player);
         analyzeEnemyShips(player);
         
         // Decide whether to initiate diplomacy or engage in combat
         if (shouldInitiateDiplomacy(player)) {
            initiateDiplomacy(player);
         } else if (shouldEngageInCombat(player)) {
            engageInCombat(player);
         }
         
         // Consider invading enemy planets if advantageous
         if (shouldInvadeEnemyPlanet(player)) {
            invadeEnemyPlanet(player);
         }
      }
   }
}

void AI::decideResourceAllocation() {
   // Decide resource allocation for planets and ships
   double totalBudget = calculateTotalResourceBudget();

   decidePlanetaryActions();
   decideShipActions();
   decideEnemyActions();
}

void AI::decidePlanetaryActions() {
   // Decide actions for owned planets
   for (Planet* planet : ownedPlanets) {
      double developmentBudget = calculatePlanetDevelopmentBudget(planet);
      double infrastructureBudget = calculatePlanetInfrastructureBudget(planet);
      double defenseBudget = calculatePlanetDefenseBudget(planet);
      
      // Allocate resources for development
      if (developmentBudget > 0) {
         allocateResourcesForDevelopment(planet, developmentBudget);
      }
      
      // Allocate resources for infrastructure
      if (infrastructureBudget > 0) {
         allocateResourcesForInfrastructure(planet, infrastructureBudget);
      }
      
      // Allocate resources for defense
      if (defenseBudget > 0) {
         allocateResourcesForDefense(planet, defenseBudget);
      }
   }
}

void AI::decideShipActions() {
   // Decide actions for owned ships
   for (Ship* ship : ownedShips) {
      double weaponUpgradeBudget = calculateShipWeaponUpgradeBudget(ship);
      double shieldUpgradeBudget = calculateShipShieldUpgradeBudget(ship);
      // Upgrade ship weapons and shields based on the calculated budgets
      upgradeShipWeapons(ship, weaponUpgradeBudget);
      upgradeShipShields(ship, shieldUpgradeBudget);
      
      // Engage or avoid enemy ships based on ship capabilities and enemy strength
      if (shouldEngageEnemy(ship)) {
         engageEnemyShip(ship);
      } else {
         avoidEnemyShip(ship);
      }
   }
}

void AI::decideEnemyActions() {
   // Decide actions related to enemy players
   for (Player* player : players) {
      if (player != aiPlayer) {
         // Analyze enemy player's strength, owned planets, and ships
         analyzeEnemyStrength(player);
         analyzeEnemyPlanets(player);
         analyzeEnemyShips(player);
         
         // Decide whether to initiate diplomacy or engage in combat
         if (shouldInitiateDiplomacy(player)) {
            initiateDiplomacy(player);
         } else if (shouldEngageInCombat(player)) {
            engageInCombat(player);
         }
         
         // Consider invading enemy planets if advantageous
         if (shouldInvadeEnemyPlanet(player)) {
            invadeEnemyPlanet(player);
         }
      }
   }
}

void AI::decidePlanetaryActions() {
   // Decide actions for owned planets
   for (Planet* planet : ownedPlanets) {
      double developmentBudget = calculatePlanetDevelopmentBudget(planet);
      double infrastructureBudget = calculatePlanetInfrastructureBudget(planet);
      double defenseBudget = calculatePlanetDefenseBudget(planet);
      // Allocate resources and perform actions based on the calculated budgets
   }
}

void AI::decideShipActions() {
   // Decide actions for owned ships
   for (Ship* ship : ownedShips) {
      double weaponUpgradeBudget = calculateShipWeaponUpgradeBudget(ship);
      double shieldUpgradeBudget = calculateShipShieldUpgradeBudget(ship);
      // Upgrade ship weapons and shields based on the calculated budgets
      upgradeShipWeapons(ship, weaponUpgradeBudget);
      upgradeShipShields(ship, shieldUpgradeBudget);
      
      // Engage or avoid enemy ships based on ship capabilities and enemy strength
      for (Ship* enemyShip : enemyShips) {
         if (shouldEngageEnemyShip(ship, enemyShip)) {
            engageEnemyShip(ship, enemyShip);
         } else {
            avoidEnemyShip(ship, enemyShip);
         }
      }
   }
}

void AI::decideEnemyActions() {
   // Decide actions related to enemy players
   for (Player* player : players) {
      if (player != aiPlayer) {
         // Analyze enemy player's strength, owned planets, and ships
         // Decide whether to initiate diplomacy or engage in combat
         if (shouldInvadeEnemyPlanet(player)) {
            invadeEnemyPlanet(player);
         }
      }
   }
}

double AI::calculatePlanetDevelopmentBudget(Planet* planet) {
   // Calculate development budget for the planet
   double baseIncome = planet->getBaseIncome();
   double populationFactor = planet->getPopulation() / 1000.0;
   double developmentFactor = 0.3; // Adjust this value as needed
   return baseIncome * populationFactor * developmentFactor;
}

double AI::calculatePlanetInfrastructureBudget(Planet* planet) {
   // Calculate infrastructure budget for the planet
   double baseIncome = planet->getBaseIncome();
   double populationFactor = planet->getPopulation() / 1000.0;
   double infrastructureFactor = 0.4; // Adjust this value as needed
   return baseIncome * populationFactor * infrastructureFactor;
}

double AI::calculatePlanetDefenseBudget(Planet* planet) {
   // Calculate defense budget for the planet
   double baseIncome = planet->getBaseIncome();
   double populationFactor = planet->getPopulation() / 1000.0;
   double defenseFactor = 0.3; // Adjust this value as needed
   return baseIncome * populationFactor * defenseFactor;
}

double AI::calculateShipWeaponUpgradeBudget(Ship* ship) {
   // Calculate weapon upgrade budget for the ship
   double baseIncome = ship->getBaseIncome();
   double weaponFactor = 0.5; // Adjust this value as needed
   return baseIncome * weaponFactor;
}

double AI::calculateShipShieldUpgradeBudget(Ship* ship) {
   // Calculate shield upgrade budget for the ship
   double baseIncome = ship->getBaseIncome();
   double shieldFactor = 0.5; // Adjust this value as needed
   return baseIncome * shieldFactor;
}
void AI::engageEnemy(Ship* ship) {
   // Engage enemy ships
   // Analyze enemy ship's strength and capabilities
   // Decide on the best strategy to engage the enemy ship
   // Consider using weapons, shields, or evasive maneuvers
   // Adjust tactics based on the outcome of the engagement
   
   // Calculate the relative strength of the enemy ship
   double enemyStrength = calculateEnemyShipStrength(ship);
   double ourStrength = calculateOurShipStrength();
   
   if (enemyStrength > ourStrength) {
      // Enemy ship is stronger, prioritize evasive maneuvers and defensive tactics
      useEvasiveManeuvers(ship);
      prioritizeShields(ship);
   } else if (enemyStrength < ourStrength) {
      // Our ship is stronger, prioritize offensive tactics
      useOffensiveWeapons(ship);
      pursueEnemyShip(ship);
   } else {
      // Ships are evenly matched, balance offensive and defensive tactics
      useBalancedTactics(ship);
   }
   
   // Continuously monitor the engagement and adjust tactics as needed
   while (ship->isEngaged()) {
      assessEngagementStatus(ship);
      adjustTactics(ship);
   }
}
void AI::avoidEnemy(Ship* ship) {
   // Avoid enemy ships
   // Analyze enemy ship's strength and capabilities
   // Decide on the best strategy to avoid the enemy ship
   // Consider using evasive maneuvers or retreating to a safe location
   // Adjust tactics based on the success of the avoidance
   
   // Calculate the relative strength of the enemy ship
   double enemyStrength = calculateEnemyShipStrength(ship);
   double ourStrength = calculateOurShipStrength();
   
   if (enemyStrength > ourStrength) {
      // Enemy ship is stronger, prioritize retreating to a safe location
      retreatToSafeLocation(ship);
   } else {
      // Use evasive maneuvers to avoid the enemy ship
      useEvasiveManeuvers(ship);
   }
   
   // Continuously monitor the avoidance and adjust tactics as needed
   while (ship->isBeingPursued()) {
      assessAvoidanceStatus(ship);
      adjustAvoidanceTactics(ship);
   }
}

void AI::initiateDiplomacy(Player* player) {
   // Initiate diplomacy with other players
   // Analyze the player's strength, owned planets, and ships
   // Decide on the best approach for diplomacy (e.g., trade, alliance, non-aggression pact)
   // Consider the potential benefits and risks of diplomacy with the player
   // Adjust diplomatic strategy based on the player's response and actions

   // Analyze player's strength
   int playerStrength = evaluatePlayerStrength(player);

   // Analyze player's owned planets and ships
   int numPlanets = player->getOwnedPlanets().size();
   int numShips = player->getOwnedShips().size();

   // Decide on the best diplomatic approach
   std::string diplomaticApproach;
   if (playerStrength < ourStrength && numPlanets > 0) {
      diplomaticApproach = "Trade";
   } else if (playerStrength > ourStrength && numShips > ourShips) {
      diplomaticApproach = "Alliance";
   } else {
      diplomaticApproach = "Non-aggression Pact";
   }

   // Consider benefits and risks
   double benefitScore = evaluateDiplomacyBenefits(player, diplomaticApproach);
   double riskScore = evaluateDiplomacyRisks(player, diplomaticApproach);

   // Adjust strategy based on response and actions
   if (player->acceptDiplomacy(diplomaticApproach)) {
      if (player->fulfillsDiplomacyTerms()) {
         maintainDiplomaticTies(player);
      } else {
         reassessDiplomaticStrategy(player);
      }
   } else {
      considerAlternativeApproaches(player);
   }
}

void AI::engageInCombat(Player* player) {
   // Engage in combat with enemy players
   // Analyze the enemy player's strength, owned planets, and ships
   // Decide on the best strategy for combat (e.g., direct assault, guerrilla tactics, economic warfare)
   // Consider the potential outcomes and consequences of engaging in combat with the player
   // Adjust combat strategy based on the progress and results of the engagement
   
   // Analyze enemy player's strength
   int enemyStrength = evaluatePlayerStrength(player);

   // Analyze enemy player's owned planets and ships  
   int numEnemyPlanets = player->getOwnedPlanets().size();
   int numEnemyShips = player->getOwnedShips().size();

   // Decide on the best combat strategy
   std::string combatStrategy;
   if (enemyStrength < ourStrength && numEnemyShips < ourShips) {
      combatStrategy = "Direct Assault";
   } else if (enemyStrength > ourStrength && numEnemyPlanets > 0) {
      combatStrategy = "Guerrilla Tactics";  
   } else {
      combatStrategy = "Economic Warfare";
   }

   // Consider potential outcomes and consequences
   double successProbability = evaluateCombatSuccess(player, combatStrategy);
   double damagePotential = evaluateCombatDamage(player, combatStrategy);

   // Adjust strategy based on progress and results
   if (isCombatProgressFavorable()) {
      intensifyCombatEfforts(player);
   } else {
      reassessCombatStrategy(player);
      if (shouldRetreat()) {
         initiateRetreat(player);
      }
   }
}

void AI::invadePlanet(Planet* planet) {
   // Invade enemy planets
   // Analyze the planet's defenses, population, and strategic value
   // Decide on the best approach for invasion (e.g., full-scale assault, infiltration, siege)
   // Consider the resources required and potential gains from invading the planet
   // Adjust invasion strategy based on the resistance encountered and the progress of the invasion
   
   // Calculate the required fleet strength based on the planet's defenses
   int requiredFleetStrength = calculateRequiredFleetStrength(planet);
   
   // Check if the available fleet strength is sufficient for invasion
   if (availableFleetStrength >= requiredFleetStrength) {
      // Launch the invasion
      launchInvasion(planet);
      
      // Monitor the progress of the invasion
      monitorInvasionProgress(planet);
      
      // Adjust the invasion strategy based on the resistance encountered
      adjustInvasionStrategy(planet);
   } else {
      // Insufficient fleet strength, consider alternative strategies or reinforcements
      considerAlternativeStrategies(planet);
   }
}

double AI::calculateTotalResourceBudget() {
   // Calculate total resource budget
   double totalBudget = 0.0;
   for (Planet* planet : aiPlayer->getOwnedPlanets()) {
      totalBudget += calculatePlanetDevelopmentBudget(planet);
      totalBudget += calculatePlanetInfrastructureBudget(planet);
      totalBudget += calculatePlanetDefenseBudget(planet);
   }
   for (Ship* ship : aiPlayer->getOwnedShips()) {
      totalBudget += calculateShipWeaponUpgradeBudget(ship);
      totalBudget += calculateShipShieldUpgradeBudget(ship);
   }
   return totalBudget;
}
void AI::allocateResourceProduction(ResourceType resource, double budget) {
   // Allocate resource production based on budget
   // Analyze the current resource production and storage levels
   // Determine the optimal allocation of the budget to maximize resource production
   // Consider factors such as planet type, infrastructure, and technology level
   // Adjust resource production allocation based on the AI's strategic priorities and goals
   
   // Get the list of owned planets
   vector<Planet*> ownedPlanets = aiPlayer->getOwnedPlanets();
   
   // Calculate the total resource production and storage capacity
   double totalProduction = 0.0;
   double totalStorageCapacity = 0.0;
   for (Planet* planet : ownedPlanets) {
      totalProduction += planet->getResourceProduction(resource);
      totalStorageCapacity += planet->getResourceStorageCapacity(resource);
   }
   
   // Determine the optimal allocation of the budget based on planet characteristics
   for (Planet* planet : ownedPlanets) {
      double allocationFactor = calculateAllocationFactor(planet, resource);
      double allocation = budget * allocationFactor;
      
      // Allocate the budget to the planet's resource production
      planet->allocateResourceProduction(resource, allocation);
   }
   
   // Adjust resource production allocation based on strategic priorities and goals
   adjustResourceAllocationStrategy(resource);
}

Ship* AI::selectTarget(Ship* ship, const std::vector<Ship*>& targets) {
   // Select a target ship from the available targets
   // Analyze each target ship's capabilities, weaknesses, and strategic value
   // Consider factors such as ship type, weapons, shields, and crew experience
   // Evaluate the potential risks and rewards of engaging each target
   // Select the target that aligns with the AI's combat strategy and objectives
   // Return the selected target ship
   if (targets.empty()) {
      return nullptr;
   }
   
   Ship* selectedTarget = nullptr;
   double maxTargetValue = 0.0;
   
   for (Ship* target : targets) {
      double targetValue = evaluateTargetValue(ship, target);
      if (targetValue > maxTargetValue) {
         maxTargetValue = targetValue;
         selectedTarget = target;
      }
   }
   
   return selectedTarget;
}

double AI::evaluateTargetValue(Ship* attacker, Ship* target) {
   // Evaluate the value of targeting a specific ship
   // Consider factors such as ship type, weapons, shields, and crew experience
   // Analyze the potential damage inflicted and received
   // Assess the strategic importance of the target
   // Return a numeric value representing the target's value
   
   double targetValue = 0.0;
   
   // Calculate the target value based on ship attributes and strategic factors
   double weaponFactor = target->getWeaponStrength() / attacker->getShieldStrength();
   double shieldFactor = target->getShieldStrength() / attacker->getWeaponStrength();
   double crewFactor = target->getCrewExperience() / attacker->getCrewExperience();
   
   double damageInflictedFactor = calculatePotentialDamageInflicted(attacker, target);
   double damageReceivedFactor = calculatePotentialDamageReceived(attacker, target);
   
   double strategicValue = assessStrategicValue(target);
   
   targetValue = weaponFactor + shieldFactor + crewFactor + damageInflictedFactor - damageReceivedFactor + strategicValue;
   
   return targetValue;
}

double AI::calculateDistance(const sf::Vector2f& position1, const sf::Vector2f& position2) {
   // Calculate the distance between two positions
   return std::sqrt(std::pow(position2.x - position1.x, 2) + std::pow(position2.y - position1.y, 2));
}

// DefenseDrone.h
#ifndef DEFENSE_DRONE_H
#define DEFENSE_DRONE_H

#include "Ship.h"

class DefenseDrone : public Ship {
private:
   double scanRange;
   double interceptSpeed;
   double interceptRange;
   // Add other defense drone properties

public:
   DefenseDrone(int owner, const sf::Vector2f& position);

   void update(double deltaTime) override;

   double getScanRange() const;
   double getInterceptSpeed() const;
   double getInterceptRange() const;
   // Add other getter methods

   void setScanRange(double range);
   void setInterceptSpeed(double speed);
   void setInterceptRange(double range);
   // Add other setter methods

   void scanForEnemies();
   void interceptEnemy(Ship* enemy);
   bool isEnemyInRange(Ship* enemy) const;
   // Add other defense drone actions
};

#endif

// DefenseDrone.cpp
#include "DefenseDrone.h"

DefenseDrone::DefenseDrone(int owner, const sf::Vector2f& position)
   : Ship(owner, position), scanRange(100.0) {}

void DefenseDrone::update(double deltaTime) {
   Ship::update(deltaTime);

   scanForEnemies();
}

double DefenseDrone::getScanRange() const {
   return scanRange;
}

void DefenseDrone::setScanRange(double range) {
   scanRange = range;
}

void DefenseDrone::scanForEnemies() {
   // Scan for enemy ships within the scan range
   std::vector<Ship*> enemyShips = GameManager::getInstance().getEnemyShipsInRange(getPosition(), scanRange, getOwner());
   
   if (!enemyShips.empty()) {
      // Select the closest enemy ship
      Ship* closestEnemy = enemyShips[0];
      double minDistance = getPosition().distance(closestEnemy->getPosition());
      
      for (size_t i = 1; i < enemyShips.size(); ++i) {
         double distance = getPosition().distance(enemyShips[i]->getPosition());
         if (distance < minDistance) {
            closestEnemy = enemyShips[i];
            minDistance = distance;
         }
      }
      
      interceptEnemy(closestEnemy);
   }
}

void DefenseDrone::interceptEnemy(Ship* enemy) {
   // Intercept and attack enemy ships
   if (enemy) {
      sf::Vector2f direction = enemy->getPosition() - getPosition();
      double distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
      direction /= distance;
      
      setVelocity(direction * getMaxSpeed());
      
      if (distance <= getAttackRange()) {
         attack(enemy);
      }
   }
}

// UIManager.h
#ifndef UI_MANAGER_H
#define UI_MANAGER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "GameState.h"

class UIManager {
private:
   sf::RenderWindow& window;
   GameState& gameState;
   // Add other UI elements and properties

public:
   UIManager(sf::RenderWindow& window, GameState& gameState);

   void handleInput(const sf::Event& event);
   void update(double deltaTime);
   void render();

private:
   void renderPlanetInfo(Planet* planet);
   void renderShipInfo(Ship* ship);
   void renderPlayerInfo(Player* player);
   void renderMinimap();
   void renderShipMovement(Ship* ship);
   void renderDefenseDroneInfo(DefenseDrone* drone);
   void renderResourceInfo(Player* player);
   void renderBuildQueue(Planet* planet);
   // Add other UI rendering methods

};

#endif

// UIManager.cpp
#include "UIManager.h"

UIManager::UIManager(sf::RenderWindow& window, GameState& gameState)
   : window(window), gameState(gameState) {}
void UIManager::handleInput(const sf::Event& event) {
   // Handle UI input events
   switch (event.type) {
      case sf::Event::Closed:
         window.close();
         break;
      case sf::Event::KeyPressed:
         // Handle key presses
         break;
      case sf::Event::MouseButtonPressed:
         // Handle mouse button presses
         break;
      case sf::Event::MouseMoved:
         // Handle mouse movement
         break;
      default:
         break;
   }
}

void UIManager::update(double deltaTime) {
   // Update UI elements based on game state
   // Update planet info
   if (gameState.getSelectedPlanet() != nullptr) {
      renderPlanetInfo(gameState.getSelectedPlanet());
   }

   // Update ship info
   if (gameState.getSelectedShip() != nullptr) {
      renderShipInfo(gameState.getSelectedShip());
   }

   // Update player info
   renderPlayerInfo(gameState.getCurrentPlayer());

   // Update minimap
   renderMinimap();

   // Update ship movement
   for (Ship* ship : gameState.getShips()) {
      renderShipMovement(ship);
   }

   // Update defense drone info
   for (DefenseDrone* drone : gameState.getDefenseDrones()) {
      renderDefenseDroneInfo(drone);
   }

   // Update resource info
   renderResourceInfo(gameState.getCurrentPlayer());
}

void UIManager::render() {
   // Render UI elements
   renderPlanetInfo(gameState.getSelectedPlanet());
   renderShipInfo(gameState.getSelectedShip());
   renderPlayerInfo(gameState.getCurrentPlayer());
   renderMinimap();
   renderShipMovement(gameState.getSelectedShip());
}
void UIManager::renderPlanetInfo(Planet* planet) {
   // Render planet information
   if (planet) {
      // Display planet name
      sf::Text planetName;
      planetName.setString(planet->getName());
      planetName.setFont(gameState.getFont());
      planetName.setCharacterSize(24);
      planetName.setFillColor(sf::Color::White);
      planetName.setPosition(10.f, 10.f);
      window.draw(planetName);

      // Display planet resources
      sf::Text planetResources;
      std::string resourcesString = "Resources: ";
      resourcesString += std::to_string(planet->getResources());
      planetResources.setString(resourcesString);
      planetResources.setFont(gameState.getFont());
      planetResources.setCharacterSize(18);
      planetResources.setFillColor(sf::Color::White);
      planetResources.setPosition(10.f, 40.f);
      window.draw(planetResources);
   }
}

void UIManager::renderShipInfo(Ship* ship) {
   // Render ship information
   if (ship) {
      // Display ship name
      sf::Text shipName;
      shipName.setString(ship->getName());
      shipName.setFont(gameState.getFont());
      shipName.setCharacterSize(24);
      shipName.setFillColor(sf::Color::White);
      shipName.setPosition(10.f, 70.f);
      window.draw(shipName);

      // Display ship health
      sf::Text shipHealth;
      std::string healthString = "Health: ";
      healthString += std::to_string(ship->getHealth());
      shipHealth.setString(healthString);
      shipHealth.setFont(gameState.getFont());
      shipHealth.setCharacterSize(18);
      shipHealth.setFillColor(sf::Color::White);
      shipHealth.setPosition(10.f, 100.f);
      window.draw(shipHealth);
   }
}

void UIManager::renderPlayerInfo(Player* player) {
   // Render player information
   if (player) {
      // Display player name
      sf::Text playerName;
      playerName.setString(player->getName());
      playerName.setFont(gameState.getFont());
      playerName.setCharacterSize(24);
      playerName.setFillColor(sf::Color::White);
      playerName.setPosition(10.f, 130.f);
      window.draw(playerName);

      // Display player resources
      sf::Text playerResources;
      std::string resourcesString = "Resources: ";
      resourcesString += std::to_string(player->getResources());
      playerResources.setString(resourcesString);
      playerResources.setFont(gameState.getFont());
      playerResources.setCharacterSize(18);
      playerResources.setFillColor(sf::Color::White);
      playerResources.setPosition(10.f, 160.f);
      window.draw(playerResources);
   }
}

void UIManager::renderMinimap() {
   // Render minimap of the galaxy
   sf::RectangleShape minimapBackground(sf::Vector2f(200.f, 200.f));
   minimapBackground.setFillColor(sf::Color(50, 50, 50));
   minimapBackground.setPosition(window.getSize().x - 210.f, 10.f);
   window.draw(minimapBackground);

   // Render planets on the minimap
   for (const auto& planet : gameState.getPlanets()) {
      sf::CircleShape planetShape(3.f);
      planetShape.setFillColor(sf::Color::Blue);
      sf::Vector2f minimapPosition = planet->getPosition() / gameState.getGalaxySize();
      minimapPosition.x *= 200.f;
      minimapPosition.y *= 200.f;
      minimapPosition += sf::Vector2f(window.get

// Ship.h
class Ship {
private:
    bool isFreighter;
    bool isAggressive;
    int health;
    int maxHealth;
    
public:
    bool isFreighterShip() const;
    void setFreighterShip(bool isFreighter);
    bool isAggressiveShip() const;
    void setAggressiveShip(bool isAggressive);
    int getHealth() const;
    void setHealth(int health);
    int getMaxHealth() const;
    void setMaxHealth(int maxHealth);
};

// Ship.cpp
bool Ship::isFreighterShip() const {
    return isFreighter;
}

void Ship::setFreighterShip(bool isFreighter) {
    this->isFreighter = isFreighter;
}

bool Ship::isAggressiveShip() const {
    return isAggressive;
}

void Ship::setAggressiveShip(bool isAggressive) {
    this->isAggressive = isAggressive;
}

int Ship::getHealth() const {
    return health;
}

void Ship::setHealth(int health) {
    this->health = health;
}

int Ship::getMaxHealth() const {
    return maxHealth;
}

void Ship::setMaxHealth(int maxHealth) {
    this->maxHealth = maxHealth;
}

// Player.h
class Player {
private:
    std::string name;
    sf::Color color;
    int resourcesAvailable;
    std::vector<std::unique_ptr<Ship>> ownedShips;
    std::vector<Planet*> ownedPlanets;
    std::vector<Player*> allies;
    std::vector<Player*> nonAggressionPacts;

public:
    Player(const std::string& name, const sf::Color& color);

    const std::string& getName() const;
    const sf::Color& getColor() const;
    int getResourcesAvailable() const;
    const std::vector<std::unique_ptr<Ship>>& getOwnedShips() const;
    const std::vector<Planet*>& getOwnedPlanets() const;

    void addOwnedShip(std::unique_ptr<Ship> ship);
    void removeOwnedShip(const Ship* ship);
    void addOwnedPlanet(Planet* planet);
    void removeOwnedPlanet(Planet* planet);

    bool isAlliedWith(const Player& otherPlayer) const;
    bool hasNonAggressionPactWith(const Player& otherPlayer) const;
    void addAlly(Player* player);
    void removeAlly(Player* player);
    void addNonAggressionPact(Player* player);
    void removeNonAggressionPact(Player* player);

    void earnResources(int amount);
    void spendResources(int amount);
};

// Player.cpp
bool Player::isAlliedWith(const Player& otherPlayer) const {
    // Check if the player is allied with the other player
    // Iterate through the player's allies and check if otherPlayer is in the list
    for (const Player* ally : allies) {
        if (ally == &otherPlayer) {
            return true;
        }
    }
    return false;
}

bool Player::hasNonAggressionPactWith(const Player& otherPlayer) const {
    // Check if the player has a non-aggression pact with the other player
    // Iterate through the player's non-aggression pacts and check if otherPlayer is in the list
    for (const Player* pactPlayer : nonAggressionPacts) {
        if (pactPlayer == &otherPlayer) {
            return true;
        }
    }
    return false;
}

// Planet.h
class Planet {
private:
    void handleShipsArrival(std::vector<Ship*>& ships);
    void initiateCombat(std::vector<Ship*>& ships);
    bool canEscapeCombat(std::vector<Ship*>& ships, Player& player);
    void handleFreighterEscape(std::vector<Ship*>& ships, Player& player);
};

// Planet.cpp
void Planet::handleShipsArrival(std::vector<Ship*>& ships) {
    std::unordered_map<Player*, std::vector<Ship*>> factionShips;

    // Group ships by faction
    for (Ship* ship : ships) {
        Player* owner = gameState.getPlayer(ship->getOwner());
        factionShips[owner].push_back(ship);
    }

    // Check if there are multiple factions orbiting the planet
    if (factionShips.size() > 1) {
        bool shouldInitiateCombat = true;

        // Check if any faction has a freighter ship
        for (const auto& pair : factionShips) {
            Player* player = pair.first;
            const std::vector<Ship*>& playerShips = pair.second;

            bool hasFreighter = false;
            for (Ship* ship : playerShips) {
                if (ship->isFreighterShip()) {
                    hasFreighter = true;
                    break;
                }
            }

            if (hasFreighter) {
                // Allow the player to choose to escape, stay, or fight
                if (canEscapeCombat(playerShips, *player)) {
                    handleFreighterEscape(playerShips, *player);
                    shouldInitiateCombat = false;
                    break;
                }
            }
        }

        // Initiate combat if no freighter escape occurred
        if (shouldInitiateCombat) {
            initiateCombat(ships);
        }
    }
}
void Planet::initiateCombat(std::vector<Ship*>& ships) {
    // Initiate combat between the ships
    std::cout << "Combat initiated between ships orbiting " << name << std::endl;
    
    // Perform combat calculations and update ship states
    for (Ship* ship : ships) {
        // Calculate damage dealt by the ship
        int damage = ship->calculateDamage();
        
        // Apply damage to other ships
        for (Ship* targetShip : ships) {
            if (targetShip != ship) {
                targetShip->takeDamage(damage);
            }
        }
    }
    
    // Remove destroyed ships from the vector
    ships.erase(std::remove_if(ships.begin(), ships.end(), [](const Ship* ship) {
        return ship->isDestroyed();
    }), ships.end());
}

bool Planet::canEscapeCombat(std::vector<Ship*>& ships, Player& player) {
    // Check if the player's ships can escape combat
    int totalEnemyStrength = 0;
    int playerStrength = 0;

    for (Ship* ship : ships) {
        if (ship->getOwner() != player.getId()) {
            totalEnemyStrength += ship->getCombatStrength();
        } else {
            playerStrength += ship->getCombatStrength();
        }
    }

    // Allow escape if player strength is less than half of total enemy strength
    return playerStrength < totalEnemyStrength / 2;
}

void Planet::handleFreighterEscape(std::vector<Ship*>& ships, Player& player) {
    // Handle the escape of the freighter ship
    // Find the nearest other planet in the galaxy
    Planet* nearestPlanet = findNearestPlanet();

    // Calculate the number of turns to reach the nearest planet based on ship speed
    int turnsToReach = calculateTurnsToReach(ships, nearestPlanet);

    // Move the freighter ship to the nearest planet
    for (Ship* ship : ships) {
        if (ship->isFreighterShip()) {
            ship->setTargetPlanet(nearestPlanet);
            ship->setTurnsToReachTarget(turnsToReach);
            break;
        }
    }
}

Planet* Planet::findNearestPlanet() {
    // Find the nearest planet in the galaxy
    double minDistance = std::numeric_limits<double>::max();
    Planet* nearestPlanet = nullptr;

    for (Planet* planet : galaxy->getPlanets()) {
        if (planet != this) {
            double distance = calculateDistance(this, planet);
            if (distance < minDistance) {
                minDistance = distance;
                nearestPlanet = planet;
            }
        }
    }

    return nearestPlanet;
}

int Planet::calculateTurnsToReach(std::vector<Ship*>& ships, Planet* targetPlanet) {
    // Calculate the number of turns to reach the target planet based on ship speed
    double distance = calculateDistance(this, targetPlanet);
    int maxTurns = 0;

    for (Ship* ship : ships) {
        if (ship->isFreighterShip()) {
            double speed = ship->getSpeed();
            int turns = static_cast<int>(std::ceil(distance / speed));
            maxTurns = std::max(maxTurns, turns);
        }
    }

    return maxTurns;
}

// GameState.h
class GameState {
private:
    void updateShipMovement(double deltaTime);
    void moveFreighterToNearestPlanet();
};

// GameState.cpp
void GameState::updateShipMovement(double deltaTime) {
    for (Ship& ship : ships) {
        if (ship.hasTargetPlanet()) {
            Planet* targetPlanet = ship.getTargetPlanet();
            double distance = calculateDistance(ship.getPosition(), targetPlanet->getPosition());
            double speed = ship.getSpeed();

            // Update the ship's position based on its speed and target planet
            sf::Vector2f direction = targetPlanet->getPosition() - ship.getPosition();
            sf::Vector2f movement = direction / static_cast<float>(distance) * static_cast<float>(speed * deltaTime);
            ship.setPosition(ship.getPosition() + movement);

            // Check if the ship has reached the target planet
            if (distance <= speed * deltaTime) {
                ship.setTargetPlanet(nullptr);
                targetPlanet->handleShipsArrival({&ship});
            }
        }
    }
}

// Ship.h
class Ship {
private:
   // ...
   int speed;
   bool isDreadnought;
   bool isDrone;
   bool isFreighter;
   // ...

public:
   // ...
   int getSpeed() const;
   void setSpeed(int speed);
   bool isDreadnoughtShip() const;
   void setDreadnoughtShip(bool isDreadnought);
   bool isDroneShip() const;
   void setDroneShip(bool isDrone);
   bool isFreighterShip() const;
   void setFreighterShip(bool isFreighter);
   // ...
};

// Ship.cpp
int Ship::getSpeed() const {
   return speed;
}

void Ship::setSpeed(int speed) {
   this->speed = speed;
}

bool Ship::isDreadnoughtShip() const {
   return isDreadnought;
}

void Ship::setDreadnoughtShip(bool isDreadnought) {
   this->isDreadnought = isDreadnought;
}

bool Ship::isDroneShip() const {
   return isDrone;
}

void Ship::setDroneShip(bool isDrone) {
   this->isDrone = isDrone;
}

// Planet.h
class Planet {
private:
   // ...
   void handleShipsInOrbit();
   void openFleetDialogue(Player& player, std::vector<Ship*>& ships);
   bool canPlayerEscapeCombat(Player& player, std::vector<Ship*>& ships);
   void initiateCombat(std::vector<Ship*>& ships);
   // ...
};

// Planet.cpp
void Planet::handleShipsInOrbit() {
   std::unordered_map<Player*, std::vector<Ship*>> factionShips;

   // Group ships by faction
   for (Ship* ship : orbitalShips) {
       Player* owner = gameState.getPlayer(ship->getOwner());
       factionShips[owner].push_back(ship);
   }

   // Handle fleet dialogues for each faction
   for (const auto& pair : factionShips) {
       Player* player = pair.first;
       std::vector<Ship*>& ships = pair.second;
       
       // Check if player can escape combat
       if (canPlayerEscapeCombat(*player, ships)) {
           // Player escaped, skip combat
           continue;
       }
       
       // Initiate combat for the faction's ships
       initiateCombat(ships);
   }
}

void Planet::openFleetDialogue(Player& player, std::vector<Ship*>& ships) {
      // Open the fleet dialogue for the player
   std::cout << "Fleet Dialogue for Player: " << player.getName() << std::endl;
   std::cout << "Options:" << std::endl;
   std::cout << "1. Attack" << std::endl;
   std::cout << "2. Escape" << std::endl;
   std::cout << "3. Stay" << std::endl;

   int choice;
   std::cin >> choice;

   switch (choice) {
       case 1:
           // Handle attack option
           initiateCombat(ships);
           break;
       case 2:
           // Handle escape option
           if (canPlayerEscapeCombat(player, ships)) {
               // Player successfully escapes
               std::cout << "Player " << player.getName() << " escaped combat." << std::endl;
           } else {
               // Player cannot escape, initiate combat
               std::cout << "Player " << player.getName() << " cannot escape. Initiating combat." << std::endl;
               initiateCombat(ships);
           }
           break;
       case 3:
           // Handle stay option
           std::cout << "Player " << player.getName() << " chooses to stay." << std::endl;
           break;
       default:
           std::cout << "Invalid choice. Defaulting to stay." << std::endl;
           break;
   }


bool Planet::canPlayerEscapeCombat(Player& player, std::vector<Ship*>& ships) {
   int playerFleetSpeed = calculateFleetSpeed(ships);

   for (const auto& pair : factionShips) {
       Player* otherPlayer = pair.first;
       if (otherPlayer != &player) {
           std::vector<Ship*>& otherShips = pair.second;
           int otherFleetSpeed = calculateFleetSpeed(otherShips);
           if (playerFleetSpeed < otherFleetSpeed) {
               return true;
           }
       }
   }

   return false;
}
void Planet::initiateCombat(std::vector<Ship*>& ships) {
   // Determine the order of combat based on ship initiative (speed + random factor)
   std::vector<Ship*> combatOrder = ships;
   std::sort(combatOrder.begin(), combatOrder.end(), [](const Ship* a, const Ship* b) {
       return a->getInitiative() > b->getInitiative();
   });

   // Perform combat rounds until one side is defeated or escapes
   bool combatOngoing = true;
   while (combatOngoing) {
       // Each ship takes its turn based on the combat order
       for (Ship* ship : combatOrder) {
           if (ship->isDestroyed()) {
               continue;
           }

           // Ship selects a target and attacks
           Ship* target = selectTarget(ship, ships);
           if (target) {
               ship->attackShip(*target);
           }
       }

       // Check if combat should continue
       combatOngoing = shouldContinueCombat(ships);
   }

   // Remove destroyed ships from the ships vector
   ships.erase(std::remove_if(ships.begin(), ships.end(), [](const Ship* ship) {
       return ship->isDestroyed();
   }), ships.end());
}


int Planet::calculateFleetSpeed(std::vector<Ship*>& ships) {
   int minSpeed = std::numeric_limits<int>::max();
   for (Ship* ship : ships) {
       int speed = ship->getSpeed();
       if (ship->isDroneShip()) {
           speed = 1;
       }
       minSpeed = std::min(minSpeed, speed);
   }
   return minSpeed;
}

// GameState.h
class GameState {
private:
   // ...
   void handleShipMovement(double deltaTime);
   void handlePlanetArrivals();
   void handleCombat();
};

// GameState.cpp
void GameState::handleShipMovement(double deltaTime) {
   for (Ship& ship : ships) {
       if (ship.hasTargetPlanet()) {
           Planet* targetPlanet = ship.getTargetPlanet();
           double distance = calculateDistance(ship.getPosition(), targetPlanet->getPosition());
           double speed = ship.getSpeed();
           
           // Calculate the time it takes for the ship to reach the target planet
           double travelTime = distance / speed;
           
           // Update the ship's position based on the elapsed time
           if (travelTime <= deltaTime) {
               // Ship reaches the target planet within the current frame
               ship.setPosition(targetPlanet->getPosition());
               ship.setTargetPlanet(nullptr);
               // TODO: Handle ship arrival at the planet (e.g., trigger events, update game state)
           } else {
               // Ship continues moving towards the target planet
               Vector2D direction = (targetPlanet->getPosition() - ship.getPosition()).normalized();
               Vector2D movement = direction * speed * deltaTime;
               ship.setPosition(ship.getPosition() + movement);
           }
       }
   }
           double speed = ship.getSpeed();

           if (ship.isDroneShip()) {
               speed = 1;
           }

           sf::Vector2f direction = targetPlanet->getPosition() - ship.getPosition();
           sf::Vector2f movement = direction / static_cast<float>(distance) * static_cast<float>(speed * deltaTime);
           ship.setPosition(ship.getPosition() + movement);

           if (distance <= speed * deltaTime) {
               ship.setTargetPlanet(nullptr);
               ship.setOrbitalPlanet(targetPlanet);
               targetPlanet->addOrbitalShip(&ship);
           }
       }
   }
}

void GameState::handlePlanetArrivals() {
   for (Planet& planet : planets) {
       planet.handleShipsInOrbit();
   }
}

void GameState::update(double deltaTime) {
   handleShipMovement(deltaTime);
   handlePlanetArrivals();
}

// CombatScreen.h
class CombatScreen {
private:
   std::vector<Ship*> combatShips;
   bool isManualMode;

public:
   CombatScreen(const std::vector<Ship*>& ships, bool isManualMode);
   void update(double deltaTime);
   void render();
   void handleInput();

private:
   void automaticCombat();
   void manualCombat();
   void renderShips();
   void renderCombatUI();
};

// CombatScreen.cpp
CombatScreen::CombatScreen(const std::vector<Ship*>& ships, bool isManualMode)
   : combatShips(ships), isManualMode(isManualMode) {}

void CombatScreen::update(double deltaTime) {
   if (!isManualMode) {
       automaticCombat();
   }
}

void CombatScreen::render() {
   renderShips();
   renderCombatUI();
}

void CombatScreen::handleInput() {
   if (isManualMode) {
       manualCombat();
   }
}
void CombatScreen::automaticCombat() {
   // Perform automatic combat
   for (Ship* ship : combatShips) {
       // Determine target ship
       Ship* target = nullptr;
       // ...

       // Calculate damage and apply it to the target ship
       int damage = calculateDamage(ship, target);
       target->applyDamage(damage);
   }
}

void CombatScreen::manualCombat() {
   // Handle manual combat input
   for (Ship* ship : combatShips) {
       if (ship->isPlayerControlled()) {
           // Get player input for targeting and weapon selection
           Ship* target = getPlayerTargetInput();
           Weapon* weapon = getPlayerWeaponInput();

           // Calculate damage and apply it to the target ship
           int damage = calculateDamage(ship, target, weapon);
           target->applyDamage(damage);
       }
   }
}

void CombatScreen::renderShips() {
   // Render the ships in the combat screen
   for (Ship* ship : combatShips) {
       // Get ship position and sprite
       Vector2 position = ship->getPosition();
       Sprite shipSprite = ship->getSprite();

       // Render the ship sprite at its position
       renderSprite(shipSprite, position);
   }
}

void CombatScreen::renderCombatUI() {
   // Render the combat UI (e.g., ship status, combat log)
   for (Ship* ship : combatShips) {
       // Render ship status (e.g., health, shields)
       renderShipStatus(ship);
   }

   // Render combat log
   renderCombatLog();
}

// Write the C++23 script for 1\_0\_0\_release de exsecutabile codice with QoL features, and anticipate any errors beforehand. Start by writing ~300 lines of code, anticipating writing another ~5700 lines of code. Next, place in another ~300 lines. Upon receiving my continuation signal, persist with ~300 lines of code, considering the ~5100 lines left to finalize this script. Carry on with the next ~300 lines of code. Extend the script with ~300 additional lines of code. Persist in your coding efforts by adding another ~300 more lines. Following my continuation signal, forge ahead with ~300 lines of code, considering that ~3900 further lines of code are planned. Following that, add ~300 more lines of code. Once you receive my continuation signal, continue with the next ~300 lines of code, bearing in mind that ~3300 additional lines of code are expected. Then, let's move on by writing further ~300 lines de codice. After that, write the next ~300 lines of code after my continuation signal with the anticipation of writing another ~2700 lines of code. Maintain code inference in another ~300 additional lines of code. As you receive my continuation signal, proceed with ~300 additional lines of code, taking into account the remaining ~2100 lines to be written. Bolster codice with ~300 lines of code. Now, proceed to write an additional ~300 lines of code. Prepare to draft ~1500 further lines of code. Advance with ~300 lines of code. Press on with ~300 additional lines of code. Forge ahead with ~300 lines of code de exsecutabile codice script. Upon receiving my continuation signal, persist with ~300 lines of code, considering the ~300 lines left to finalize this script. Finally, the next ~300 lines of code will be written after you await "Next Page" from me. For 1\_0\_0\_release in total, there will be ~6000 lines of code, requiring approximately 20 - 30 times will I need to give you a continuation signal. Despite that, you will not stop writing code knowing you have so much space to. Simply put, by the end of 1\_0\_0\_release, all essential QoL features will be incorporated (e.g., missing fucntions within "Void", keep deciding things for the code. for example, a decision you should make is that when a player tries to group a fleet with drone ships, the player will not be able to have the fleet travel to another planet within the galaxy unless that planet is owned by the player. If the planet is not owned by the player while the drone ships are en-route, then the drone ships will still continue traveling to the abandoned/killed planet. also, abandonment of planets is a thing in Spaceward Ho! when not enough funds are being allocated to a planet that doesn't turn a profit.). There will also be additional QoL adjustments made by inference along the way in writing 1\_0\_0\_release, since some lines lack some statements which other parts of the code possess. A characteristic crucial to properly integrate: retaining properties from both versions which demonstrate functional code, and making inferences across code from both end and beginning to influence code creation back at the beginning to end. Begin by writing the files which have the least dependencies, and preserve all the QoL features you can find from each struct. If there are QoL features missing, then you can draw inference to figure out what those might be.

// Write the C++23 script for 1_0_0_release de exsecutabile codice with QoL features, and anticipate any errors beforehand. Start by writing ~300 lines of code, anticipating writing another ~5700 lines of code. Next, place in another ~300 lines.

// Upon receiving my continuation signal, persist with ~300 lines of code, considering the ~5100 lines left to finalize this script.

// Carry on with the next ~300 lines of code.

// Extend the script with ~300 additional lines of code.

// Persist in your coding efforts by adding another ~300 more lines.

// Following my continuation signal, forge ahead with ~300 lines of code, considering that ~3900 further lines of code are planned.

// Following that, add ~300 more lines of code.

// Once you receive my continuation signal, continue with the next ~300 lines of code, bearing in mind that ~3300 additional lines of code are expected.

// Then, let's move on by writing further ~300 lines de codice.

// After that, write the next ~300 lines of code after my continuation signal with the anticipation of writing another ~2700 lines of code.

// Maintain code inference in another ~300 additional lines of code.

// As you receive my continuation signal, proceed with ~300 additional lines of code, taking into account the remaining ~2100 lines to be written.

// Bolster codice with ~300 lines of code.

// Now, proceed to write an additional ~300 lines of code.

// Prepare to draft ~1500 further lines of code.

// Advance with ~300 lines of code.

// Press on with ~300 additional lines of code.

// Forge ahead with ~300 lines of code de exsecutabile codice script.

// Upon receiving my continuation signal, persist with ~300 lines of code, considering the ~300 lines left to finalize this script.

// Finally, the next ~300 lines of code will be written after you await "Next Page" from me.

// For 1_0_0_release in total, there will be ~6000 lines of code, requiring approximately 20 - 30 times will I need to give you a continuation signal. Despite that, you will not stop writing code knowing you have so much space to.

// Simply put, by the end of 1_0_0_release, all essential QoL features will be incorporated (e.g., missing fucntions within "Void", keep deciding things for the code. for example, a decision you should make is that when a player tries to group a fleet with drone ships, the player will not be able to have the fleet travel to another planet within the galaxy unless that planet is owned by the player. If the planet is not owned by the player while the drone ships are en-route, then the drone ships will still continue traveling to the abandoned/killed planet. also, abandonment of planets is a thing in Spaceward Ho! when not enough funds are being allocated to a planet that doesn't turn a profit.).

// There will also be additional QoL adjustments made by inference along the way in writing 1_0_0_release, since some lines lack some statements which other parts of the code possess.

//A characteristic crucial to properly integrate: retaining properties from both versions which demonstrate functional code, and making inferences across code from both end and beginning to influence code creation back at the beginning to end.

// Begin by writing the files which have the least dependencies, and preserve all the QoL features you can find from each struct. If there are QoL features missing, then you can draw inference to figure out what those might be.

// The file directory is intended to work like this;
//open_spaceward_ho/
//├── CMakeLists.txt
//├── src/
//│   ├── CMakeLists.txt
//│   ├── main.cpp
//│   ├── game/
//│   │   ├── CMakeLists.txt
//│   │   ├── game.h
//│   │   ├── game.cpp
//│   │   ├── game_state.h
//│   │   ├── game_state.cpp
//│   │   ├── game_settings.h
//│   │   └── game_settings.cpp
//│   ├── entities/
//│   │   ├── CMakeLists.txt
//│   │   ├── planet.h
//│   │   ├── planet.cpp
//│   │   ├── ship.h
//│   │   ├── ship.cpp
//│   │   ├── player.h
//│   │   ├── player.cpp
//│   │   ├── technology.h
//│   │   ├── technology.cpp
//│   │   ├── projectile.h
//│   │   └── projectile.cpp
//│   ├── game_logic/
//│   │   ├── CMakeLists.txt
//│   │   ├── galaxy.h
//│   │   ├── galaxy.cpp
//│   │   ├── game_logic.h
//│   │   ├── game_logic.cpp
//│   │   ├── event_system.h
//│   │   ├── event_system.cpp
//│   │   ├── combat_system.h
//│   │   ├── combat_system.cpp
//│   │   ├── ai_system.h
//│   │   └── ai_system.cpp
//│   ├── rendering/
//│   │   ├── CMakeLists.txt
//│   │   ├── renderer.h
//│   │   ├── renderer.cpp
//│   │   ├── ui_renderer.h
//│   │   ├── ui_renderer.cpp
//│   │   ├── galaxy_view.h
//│   │   ├── galaxy_view.cpp
//│   │   ├── planet_view.h
//│   │   ├── planet_view.cpp
//│   │   ├── ship_designer.h
//│   │   └── ship_designer.cpp
//│   ├── input/
//│   │   ├── CMakeLists.txt
//│   │   ├── input_handler.h
//│   │   └── input_handler.cpp
//│   ├── ui/
//│   │   ├── CMakeLists.txt
//│   │   ├── ui_manager.h
//│   │   ├── ui_manager.cpp
//│   │   ├── ui_elements.h
//│   │   ├── ui_elements.cpp
//│   │   ├── screens/
//│   │   │   ├── main_menu.h
//│   │   │   ├── main_menu.cpp
//│   │   │   ├── game_screen.h
//│   │   │   ├── game_screen.cpp
//│   │   │   ├── planet_screen.h
//│   │   │   ├── planet_screen.cpp
//│   │   │   ├── ship_design_screen.h
//│   │   │   ├── ship_design_screen.cpp
//│   │   │   ├── tech_screen.h
//│   │   │   ├── tech_screen.cpp
//│   │   │   ├── diplomacy_screen.h
//│   │   │   └── diplomacy_screen.cpp
//│   ├── networking/
//│   │   ├── CMakeLists.txt
//│   │   ├── network_manager.h
//│   │   ├── network_manager.cpp
//│   │   ├── network_messages.h
//│   │   ├── network_messages.cpp
//│   │   ├── server/
//│   │   │   ├── server.h
//│   │   │   └── server.cpp
//│   │   └── client/
//│   │       ├── client.h
//│   │       └── client.cpp
//│   ├── utility/
//│   │   ├── CMakeLists.txt
//│   │   ├── resource_manager.h
//│   │   ├── resource_manager.cpp
//│   │   ├── utility.h
//│   │   └── utility.cpp
//│   ├── data/
//│   │   ├── CMakeLists.txt
//│   │   ├── save_game.h
//│   │   ├── save_game.cpp
//│   │   ├── game_data.h
//│   │   └── game_data.cpp
//│   ├── config/
//│   │   ├── CMakeLists.txt
//│   │   ├── config_manager.h
//│   │   ├── config_manager.cpp
//│   │   ├── game_config.h
//│   │   └── game_config.cpp
//│   └── scripting/
//│       ├── CMakeLists.txt
//│       ├── scripting_engine.h
//│       ├── scripting_engine.cpp
//│       ├── script_api.h
//│       └── script_api.cpp
//├── assets/
//│   ├── textures/
//│   │   ├── planets/
//│   │   ├── ships/
//│   │   ├── ui/
//│   │   └── backgrounds/
//│   ├── fonts/
//│   ├── sounds/
//│   │   ├── effects/
//│   │   └── music/
//│   └── data/
//│       ├── tech_tree.json
//│       ├── ship_data.json
//│       ├── planet_data.json
//│       ├── event_data.json
//│       └── localization/
//├── docs/
//│   ├── game_design.md
//│   ├── api_reference.md
//│   ├── scripting_guide.md
//│   └── modding_guide.md
//├── mods/
//│   ├── example_mod/
//│   └── mod_template/
//└── tests/
//├── CMakeLists.txt
//├── game_tests.cpp
//├── entity_tests.cpp
//├── game_logic_tests.cpp
//├── rendering_tests.cpp
//├── input_tests.cpp
//├── ui_tests.cpp
//├── networking_tests.cpp
//├── utility_tests.cpp
//└── scripting_tests.cpp