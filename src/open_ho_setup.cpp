#include <iostream>
#include <vector>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

// Structs
struct Planet {
    int x, y;
    int playerOwner;
    int population;
    double temperature;
    double gravity;
    double metal;
    double* incomeGenerated;
    double* devotedResources;
    std::vector<int>* orbitalShips;
    std::vector<int>* shipsInProduction;
    int terraformingLevel;
    int miningLevel;
    int shipbuildingCapacity;
    int defenseLevel;
};

struct Ship {
    int shipType;
    int attackPower;
    int defenseRating;
    int speed;
    int range;
    int miniaturizationLevel;
};

struct Technology {
    std::string name;
    int currentLevel;
    double costToUpgrade;
    std::vector<double>* effects;
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
    std::vector<int>* technologyLevels;
    std::vector<int>* planetsOwned;
    std::vector<int>* planetsSeen;
    std::vector<int>* propertiesSeenInPossessionOfOtherPlayer;
    int numberOfShipsOwned;
    int researchPoints;
    std::vector<int>* diplomacyStatus;
};

struct GUIElement {
    int upperLeftX, upperLeftY;
    int bottomRightX, bottomRightY;
};

// Classes
class Galaxy {
public:
    Galaxy();
    void updateGameState(double deltaTime);
    void handlePlayerInput();
    void renderGraphics();

private:
    std::vector<Planet> planets;
    std::vector<int> turnsTaken;
    std::vector<double> initialValues;
    std::vector<double*> populationGrowthCalculations;
    std::vector<Player> players;
    std::vector<int> windowSize;
    std::vector<GUIElement> guiElements;
    std::vector<int> assetSizes;
    std::vector<int> preloadedActions;
    std::vector<int> shipTypes;
    std::vector<int> statisticsGraphTabs;
    std::vector<int> playerActions;
    std::vector<double> allocationPercentages;
    std::vector<int> technologyNumbers;
    std::vector<double*> technologyEffectEquations;
    std::vector<int> battleData;
    std::vector<Ship> ships;
    std::vector<Technology> technologies;
};

class GameUI {
public:
    GameUI(Galaxy& galaxy);
    void renderGalaxyView();
    void displayPlanetInfo(int planetId);
    void showShipOrbits(int planetId);
    void updateTechTreeUI();
    void updateMinimap();
    void displayShipInfo(int shipId);
    void displayTechnologyInfo(int techIndex);
    void displayPlayerInfo(int playerNumber);

private:
    Galaxy& gameGalaxy;
};

class GameLogic {
public:
    GameLogic(Galaxy& galaxy);
    void calculatePopulationGrowth();
    void allocateResources();
    void handleShipMovement();
    void resolveShipCombat();
    void researchTechnology();
    void applyTechnologyEffects();
    void makeAIDecisions();
    void terraformPlanet(int planetId, int targetTemp, double targetGravity);
    void conductMining(int planetId);
    void performShipMaintenance(int playerId);
    void engageInDiplomacy(int playerId, int otherPlayerId);
    void colonizePlanet(Player& player, Planet& planet);
    void developPlanet(Player& player, Planet& planet);
    void conductEspionage(Player& player, Player& targetPlayer); 
    void conductSabotage(Player& player, Player& targetPlayer);

private:
    Galaxy& gameGalaxy;
};

class SaveGame {
public:
    SaveGame(const Galaxy& galaxy);
    void saveGameState(const std::string& filename);
    void loadGameState(const std::string& filename);

private:
    const Galaxy& gameGalaxy;
};

class AI {
public:
    AI(Galaxy& galaxy);
    void update(double deltaTime);
    void makeDecisions();
    void executeActions();

private:
    Galaxy& gameGalaxy;
    void updateObservableGameState();
    void analyzeObservableGameState();
    void updateInternalState();
    void updateGameState(double deltaTime);
    void decidePlanetaryDevelopment();
    void decideFleetMovement();
    void decideResearch();
    void decideDiplomacy();
    void developPlanets();
    void moveFleets();
    void conductResearch();
    void engageInDiplomacy();
    std::vector<Planet> observablePlanets;
    std::vector<Ship> observableShips;
    std::vector<Player> observablePlayers;
    std::vector<Technology> observableTechnologies;
    std::vector<GameEvent> observableGameEvents;
};

class GameEvent {
public:
    void trigger();

private:
    void applyRandomEventEffects();
    void displayStoryEventMessage();
    void displayStoryEventChoices();
    void handlePlayerChoice();
    void initiateDiplomaticNegotiations();
    void triggerDiplomaticActions();
    void applyChoiceEffects(int choice);
    void displayNegotiationOptions();
    void handleNegotiationChoices();
    void formAlliance();
    void establishTradeAgreement();
    void signPeaceTreaty();
    void applyNaturalDisasterEffects();  
    void applyTechnologicalBreakthroughEffects();
    void applyPirateAttackEffects();
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
    std::vector<std::string> choices;
};

class BattleSystem {
public:
    BattleSystem(Galaxy& galaxy);
    void initiateBattle(Player& attacker, Player& defender, Planet& battlePlanet);
    void simulateBattle();
    void displayBattleSummary();

private:
    Galaxy& gameGalaxy;
    Player* attacker;
    Player* defender;  
    Planet* battlePlanet;
    std::vector<Ship*> attackerShips;
    std::vector<Ship*> defenderShips;
    int round;
    void performBattleRound();
    void displayRoundSummary();
    void determineBattleOutcome();
    void resolveBattleVictory(Player& victor, Planet& planet);
    void prepareShipsForBattle(Player& player, std::vector<Ship*>& ships);
    void performShipAction(Ship* ship, std::vector<Ship*>& enemyShips); 
    void removeDestroyedShips(std::vector<Ship*>& ships);
    void displayShipStatus(const std::vector<Ship*>& ships);
    void displayShipActions(const std::vector<Ship*>& ships);
    void applyBattleEffects(Player& victor, Planet& planet);
    void awardBattleRewards(Player& victor, Planet& planet);
    Ship* selectTarget(const std::vector<Ship*>& enemyShips);
    bool isBattleOver();    
};

class Game {
public:
    Game();
    void run();
    void initiateBattle(Player& attacker, Player& defender, Planet& planet);

private:
    Galaxy gameGalaxy;
    std::vector<Player*> players;
    std::vector<AI*> aiPlayers;  
    bool isGameOver;
    void handleEvents();
    void triggerEvents();
    void checkVictoryConditions();
    void renderGraphics();
    void triggerRandomEvents();
    void triggerStoryEvents();
    void triggerDiplomaticEvents();
    void updateGameState(GameEvent* event);
    void declareWinner(Player* player);
    void renderGalaxyMap();
    void renderPlayerInterfaces();
    void renderBattleVisualizations();
    std::vector<GameEvent*> activeEvents;
};

// Planet class implementation
Planet::Planet(int x, int y, int playerOwner, int population, double temperature, double gravity, double metal)
    : x(x), y(y), playerOwner(playerOwner), population(population), temperature(temperature),
      gravity(gravity), metal(metal), terraformingLevel(0), miningLevel(0), shipbuildingCapacity(0), defenseLevel(0) {
    incomeGenerated = new double[5]{0.0, 0.0, 0.0, 0.0, 0.0};
    devotedResources = new double[5]{0.0, 0.0, 0.0, 0.0, 0.0};
    orbitalShips = new std::vector<int>();
    shipsInProduction = new std::vector<int>();
}

Planet::~Planet() {
    delete[] incomeGenerated;
    delete[] devotedResources;
    delete orbitalShips;
    delete shipsInProduction;
}

void Planet::updateIncome() {
    const double incomeFactor = 0.1;
    for (int i = 0; i < 5; ++i) {
        incomeGenerated[i] = population * devotedResources[i] * incomeFactor;
    }
}

void Planet::allocateResources(double* allocation) {
    for (int i = 0; i < 5; ++i) {
        devotedResources[i] = allocation[i] * metal;
    }
}

void Planet::buildShip(int shipType) {
    if (metal >= 100 && shipbuildingCapacity > 0) {
        shipsInProduction->push_back(shipType);
        metal -= 100;
        --shipbuildingCapacity;
    }
}

void Planet::updateTerraformingLevel(int level) {
    terraformingLevel = level;
    temperature += level * 0.1;
    gravity += level * 0.05;
}

void Planet::updateMiningLevel(int level) {
    miningLevel = level;
    metal += level * 10;
}

void Planet::updateShipbuildingCapacity(int capacity) {
    shipbuildingCapacity = capacity;
}

void Planet::updateDefenseLevel(int level) {
    defenseLevel = level;
}

void Planet::update(double deltaTime) {
    updatePopulationGrowth(deltaTime);
    updateResourceProduction(deltaTime);
    updateInfrastructure(deltaTime);
    updateDefense(deltaTime);
    applySpecialEffects(deltaTime);
}

void Planet::updatePopulationGrowth(double deltaTime) {
    double growthRate = calculateGrowthRate();
    double carryingCapacity = calculateCarryingCapacity();
    population += population * growthRate * (1 - population / carryingCapacity) * deltaTime;
}

void Planet::updateResourceProduction(double deltaTime) {
    double metalProduction = calculateMetalProduction();
    double energyProduction = calculateEnergyProduction();
    double foodProduction = calculateFoodProduction();
    metal += metalProduction * deltaTime;
    energy += energyProduction * deltaTime;
    food += foodProduction * deltaTime;
}

void Planet::updateInfrastructure(double deltaTime) {
    double infrastructureGrowth = calculateInfrastructureGrowth();
    infrastructure += infrastructureGrowth * deltaTime;
}

void Planet::updateDefense(double deltaTime) {
    double defenseGrowth = calculateDefenseGrowth();
    defense += defenseGrowth * deltaTime;
}

void Planet::applySpecialEffects(double deltaTime) {
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

// Ship class implementation  
Ship::Ship(int shipType, int attackPower, int defenseRating, int speed, int range, int miniaturizationLevel)
    : shipType(shipType), attackPower(attackPower), defenseRating(defenseRating),
      speed(speed), range(range), miniaturizationLevel(miniaturizationLevel) {}

void Ship::upgrade(int attackBonus, int defenseBonus, int speedBonus, int rangeBonus) {
    attackPower += attackBonus;
    defenseRating += defenseBonus;  
    speed += speedBonus;
    range += rangeBonus;
}

void Ship::applyMiniaturization(int level) {
    miniaturizationLevel = level;
}

void Ship::update(double deltaTime) {
    updateCombatReadiness(deltaTime); 
    updateSensorRange(deltaTime);
    updateDetection(deltaTime);
    applySpecialAbilities(deltaTime);
}

void Ship::updateCombatReadiness(double deltaTime) {
    double suppliesEffect = calculateSuppliesEffect();  
    double moraleEffect = calculateMoraleEffect();
    double conditionEffect = calculateConditionEffect();
    combatReadiness = baseCombatReadiness * suppliesEffect * moraleEffect * conditionEffect;  
}

void Ship::updateSensorRange(double deltaTime) {
    double sensorUpgradeEffect = calculateSensorUpgradeEffect();
    sensorRange = baseSensorRange * sensorUpgradeEffect;
}

void Ship::updateDetection(double deltaTime) {
    std::vector<Ship*> nearbyShips = detectNearbyShips();
    std::vector<Planet*> nearbyPlanets = detectNearbyPlanets();
    updateTarget(nearbyShips, nearbyPlanets);
    engageInCombat(deltaTime);
}

void Ship::applySpecialAbilities(double deltaTime) {
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

// Technology class implementation
Technology::Technology(const std::string& name, int currentLevel, double costToUpgrade) 
    : name(name), currentLevel(currentLevel), costToUpgrade(costToUpgrade) {
    effects = new std::vector<double>();        
}

Technology::~Technology() {
    delete effects;
}

void Technology::upgrade() {
    ++currentLevel;
    costToUpgrade *= 1.5;
}

void Technology::addEffect(double effect) {
    effects->push_back(effect);
}

double Technology::getEffect(int index) const {
    if (index >= 0 && index < effects->size()) {
        return effects->at(index);
    }
    return 0.0;
}

void Technology::update(double deltaTime) {
    updateResearchProgress(deltaTime);
    if (isResearched()) {
        applyEffects();  
    }
}

void Technology::updateResearchProgress(double deltaTime) {
    double researchProgress = calculateResearchProgress(deltaTime);
    researchedPoints += researchProgress * deltaTime;
}

void Technology::applyEffects() {
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

// Player class implementation
Player::Player(int playerNumber, const std::string& playerName, double temperaturePreference, double gravityPreference)
    : playerNumber(playerNumber), playerName(playerName), temperaturePreference(temperaturePreference),
      gravityPreference(gravityPreference), totalPopulation(0), totalFundsAccumulated(0.0),
      totalFundsInBank(0.0), totalGrossIncomePerTurn(0.0), totalFundsSpentOnTechnology(0.0),
      numberOfShipsOwned(0), researchPoints(0) {
    technologyLevels = new std::vector<int>();
    planetsOwned = new std::vector<int>();
    planetsSeen = new std::vector<int>();
    propertiesSeenInPossessionOfOtherPlayer = new std::vector<int>();
    diplomacyStatus = new std::vector<int>();
}

void Player::updateTotalPopulation() {
    totalPopulation = 0;
    for (int planetId : *planetsOwned) {
        totalPopulation += gameGalaxy.getPlanet(planetId)->getPopulation();
    }
}

void Player::updateTotalFunds() {
    totalFundsAccumulated += totalGrossIncomePerTurn;
    totalFundsInBank = totalFundsAccumulated - totalFundsSpentOnTechnology;
}

void Player::updateGrossIncome() {
    totalGrossIncomePerTurn = 0.0;
    for (int planetId : *planetsOwned) {
        totalGrossIncomePerTurn += gameGalaxy.getPlanet(planetId)->getIncome();
    }
}

void Player::investInTechnology(int technologyIndex, double funds) {
    if (funds <= totalFundsInBank) {
        totalFundsSpentOnTechnology += funds;
        totalFundsInBank -= funds;
        gameGalaxy.getTechnology(technologyIndex)->addResearchPoints(funds);
    }
}

void Player::addPlanetOwned(int planetId) {
    planetsOwned->push_back(planetId);
}

void Player::addPlanetSeen(int planetId) {
    planetsSeen->push_back(planetId);
}

void Player::addPropertySeenInPossessionOfOtherPlayer(int propertyId) {
    propertiesSeenInPossessionOfOtherPlayer->push_back(propertyId);
}

void Player::updateDiplomacyStatus(int playerNumber, int status) {
    if (playerNumber >= 0 && playerNumber < diplomacyStatus->size()) {
        diplomacyStatus->at(playerNumber) = status;
    }
}

void Player::buildShip(int planetId, int shipType) {
    Planet* planet = gameGalaxy.getPlanet(planetId);
    if (planet != nullptr) {
        planet->buildShip(shipType);
        ++numberOfShipsOwned;
    }
}

void Player::update(double deltaTime) {
    updateResourceGeneration(deltaTime);
    updateResearchProgress(deltaTime);
    updateShipProduction(deltaTime);
    updateShipMaintenance(deltaTime);
    updateDiplomacy(deltaTime);
    updateEspionage(deltaTime);
}

void Player::updateResourceGeneration(double deltaTime) {
    double metalGeneration = calculateMetalGeneration(planetsOwned);
    double energyGeneration = calculateEnergyGeneration(planetsOwned);
    double foodGeneration = calculateFoodGeneration(planetsOwned);
    metal += metalGeneration * deltaTime;
    energy += energyGeneration * deltaTime;
    food += foodGeneration * deltaTime;
}

void Player::updateResearchProgress(double deltaTime) {
    for (int i = 0; i < technologies.size(); ++i) {
        double researchProgress = calculateResearchProgress(technologies[i], researchPoints[i], deltaTime);
        technologies[i].addResearchProgress(researchProgress);
        if (technologies[i].isResearched()) {
            applyTechnologyEffects(technologies[i]);
        }
    }
}

void Player::updateShipProduction(double deltaTime) {
    for (int i = 0; i < planets.size(); ++i) {
        int shipProduction = calculateShipProduction(planets[i]);
        planets[i].addShipProductionProgress(shipProduction * deltaTime);
        while (planets[i].isShipCompleted()) {
            Ship newShip = createShip(planets[i].getCompletedShipType());
            ships.push_back(newShip);
            planets[i].removeCompletedShip();
        }
    }
}

void Player::updateShipMaintenance(double deltaTime) {
    for (int i = 0; i < ships.size(); ++i) {
        double maintenanceCost = calculateShipMaintenanceCost(ships[i]);
        deductResources(maintenanceCost);
        applyShipMaintenanceEffects(ships[i], deltaTime);
    }
}

void Player::updateDiplomacy(double deltaTime) {
    for (int i = 0; i < diplomacyStatus.size(); ++i) {
        updateDiplomacyStatus(i, deltaTime);
        applyDiplomacyEffects(i, deltaTime);
    }
}

void Player::updateEspionage(double deltaTime) {
    for (int i = 0; i < espionageMissions.size(); ++i) {
        updateEspionageMissionProgress(espionageMissions[i], deltaTime);
        if (espionageMissions[i].isCompleted()) {
            applyEspionageMissionEffects(espionageMissions[i]);
            espionageMissions.erase(espionageMissions.begin() + i);
            --i;
        }
    }
}

void Player::updateResourceIncome(double deltaTime) {
    resourceIncome = calculateResourceIncome(ownedPlanets, deltaTime);
}

void Player::updateResearchProgress(double deltaTime) {
    for (Technology& technology : researchedTechnologies) {
        technology.update(deltaTime);
    }
}

void Player::updateDiplomacy(double deltaTime) {
    for (Player& otherPlayer : diplomacyStatus) {
        updateDiplomaticRelations(otherPlayer, deltaTime);
    }
}

void Player::updateFleet(double deltaTime) {
    for (Ship& ship : ownedShips) {
        ship.update(deltaTime);
    }
}

// Resource management
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

// Ship management
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


// Planet management
void Player::colonizePlanet(Planet* planet) {
    if (planet->getOwner() == nullptr && canAfford(getColonizationCost(planet))) {
        consumeResources(getColonizationCost(planet));
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

// Technology research
void Player::researchTechnology(const std::string& techName) {
    if (canAfford(getTechMetalCost(techName), getTechEnergyCost(techName))) {
        consumeResources(getTechMetalCost(techName), getTechEnergyCost(techName));
        Technology* tech = gameState->getTechnology(techName);
        if (tech != nullptr) {
            tech->research(this);
        }
    }
}

// Diplomacy and trade
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

void Player::rejectAlliance(Player* otherPlayer) {
    // Reject the alliance proposal
}

bool Player::evaluateAllianceProposal(Player* sender) {
    // Evaluate the alliance proposal based on player's diplomatic strategy and relationship with the sender
    return true;
}

void Player::receiveWarDeclaration(Player* sender) {
    // Handle the war declaration
    enemies.push_back(sender);
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

void Player::rejectPeace(Player* otherPlayer) {
    // Reject the peace proposal
    // Notify the sender that the peace proposal was rejected
    sender->receivePeaceRejection(this);
}

bool Player::evaluatePeaceProposal(Player* sender) {
    // Evaluate the peace proposal based on player's diplomatic strategy and current relationship with the sender
    // Check if the sender is a current enemy
    if (isEnemy(sender)) {
        // Consider factors like relative military strength, economic situation, and past interactions
        // Implement the specific evaluation logic based on the game's requirements
        // For now, return true if the sender is an enemy, false otherwise
        return true;
    }
    return false;
}

void Player::removeEnemy(Player* enemy) {
    enemies.erase(std::remove(enemies.begin(), enemies.end(), enemy), enemies.end());
}

void Player::render() {
    // Render the player's UI and other visual elements
    renderUI();
    renderPlanets();
    renderFleets();
    renderDiplomacy();
}

void Player::loseResources(double amount) {
    // Deduct resources from the player
    resources -= amount;
    if (resources < 0) {
        resources = 0;
    }
}

Player::~Player() {
    delete technologyLevels;
    delete planetsOwned;
    delete planetsSeen;
    delete propertiesSeenInPossessionOfOtherPlayer;
    delete diplomacyStatus;
}

void Player::updateTotalPopulation() {
    totalPopulation = 0;
    for (int planetId : *planetsOwned) {
        totalPopulation += gameGalaxy.getPlanet(planetId)->getPopulation();
    }
}

void Player::updateTotalFunds() {
    totalFundsAccumulated += totalGrossIncomePerTurn;
    totalFundsInBank = totalFundsAccumulated - totalFundsSpentOnTechnology;
}

void Player::updateGrossIncome() {
    totalGrossIncomePerTurn = 0.0;
    for (int planetId : *planetsOwned) {
        totalGrossIncomePerTurn += gameGalaxy.getPlanet(planetId)->getIncome();
    }
}

void Player::investInTechnology(int technologyIndex, double funds) {
    if (funds <= totalFundsInBank) {
        totalFundsSpentOnTechnology += funds;
        totalFundsInBank -= funds;
        gameGalaxy.getTechnology(technologyIndex)->addResearchPoints(funds);
    }
}

void Player::addPlanetOwned(int planetId) {
    planetsOwned->push_back(planetId);
}

void Player::addPlanetSeen(int planetId) {
    planetsSeen->push_back(planetId);
}

void Player::addPropertySeenInPossessionOfOtherPlayer(int propertyId) {
    propertiesSeenInPossessionOfOtherPlayer->push_back(propertyId);
}

void Player::updateDiplomacyStatus(int playerNumber, int status) {
    if (playerNumber >= 0 && playerNumber < diplomacyStatus->size()) {
        diplomacyStatus->at(playerNumber) = status;
    }
}

void Player::buildShip(int planetId, int shipType) {
    Planet* planet = gameGalaxy.getPlanet(planetId);
    if (planet != nullptr) {
        planet->buildShip(shipType);
        ++numberOfShipsOwned;
    }
}

void Player::update(double deltaTime) {
    updateResourceGeneration(deltaTime);
    updateResearchProgress(deltaTime);
    updateShipProduction(deltaTime);
    updateShipMaintenance(deltaTime);
    updateDiplomacy(deltaTime);
    updateEspionage(deltaTime);
}

void Player::updateResourceGeneration(double deltaTime) {
    double metalGeneration = calculateMetalGeneration(planetsOwned);
    double energyGeneration = calculateEnergyGeneration(planetsOwned);
    double foodGeneration = calculateFoodGeneration(planetsOwned);
    metal += metalGeneration * deltaTime;
    energy += energyGeneration * deltaTime;
    food += foodGeneration * deltaTime;
}

void Player::updateResearchProgress(double deltaTime) {
    for (int i = 0; i < technologies.size(); ++i) {
        double researchProgress = calculateResearchProgress(technologies[i], researchPoints[i], deltaTime);
        technologies[i].addResearchProgress(researchProgress);
        if (technologies[i].isResearched()) {
            applyTechnologyEffects(technologies[i]);
        }
    }
}

void Player::updateShipProduction(double deltaTime) {
    for (int i = 0; i < planets.size(); ++i) {
        int shipProduction = calculateShipProduction(planets[i]);
        planets[i].addShipProductionProgress(shipProduction * deltaTime);
        while (planets[i].isShipCompleted()) {
            Ship newShip = createShip(planets[i].getCompletedShipType());
            ships.push_back(newShip);
            planets[i].removeCompletedShip();
        }
    }
}

void Player::updateShipMaintenance(double deltaTime) {
    for (int i = 0; i < ships.size(); ++i) {
        double maintenanceCost = calculateShipMaintenanceCost(ships[i]);
        deductResources(maintenanceCost);
        applyShipMaintenanceEffects(ships[i], deltaTime);
    }
}

void Player::updateDiplomacy(double deltaTime) {
    for (int i = 0; i < diplomacyStatus.size(); ++i) {
        updateDiplomacyStatus(i, deltaTime);
        applyDiplomacyEffects(i, deltaTime);
    }
}

void Player::updateEspionage(double deltaTime) {
    for (int i = 0; i < espionageMissions.size(); ++i) {
        updateEspionageMissionProgress(espionageMissions[i], deltaTime);
        if (espionageMissions[i].isCompleted()) {
            applyEspionageMissionEffects(espionageMissions[i]);
            espionageMissions.erase(espionageMissions.begin() + i);
            --i;
        }
    }
}

// GameUI class implementation
void GameUI::displayShipInfo(int shipId) {
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

void GameUI::displayTechnologyInfo(int techIndex) {
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

void GameUI::displayPlayerInfo(int playerNumber) {
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

// GameLogic class implementation
void GameLogic::terraformPlanet(int planetId, int targetTemp, double targetGravity) {
    Planet* planet = gameGalaxy.getPlanet(planetId);
    if (planet != nullptr) {
        double tempProgress = calculateTerraformingProgress(planet->getTemperature(), targetTemp);
        double gravityProgress = calculateTerraformingProgress(planet->getGravity(), targetGravity);
        planet->setTemperature(planet->getTemperature() + tempProgress);
        planet->setGravity(planet->getGravity() + gravityProgress);
        applyTerraformingEffects(planet);
    }
}

void GameLogic::conductMining(int planetId) {
    Planet* planet = gameGalaxy.getPlanet(planetId);
    if (planet != nullptr) {
        double miningYield = calculateMiningYield(planet->getMetal(), planet->getMiningLevel());
        planet->setMetal(planet->getMetal() - miningYield);
        applyMiningEffects(planet, miningYield);
    }
}

void GameLogic::performShipMaintenance(int playerId) {
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

void GameLogic::engageInDiplomacy(int playerId, int otherPlayerId) {
    Player* player = gameGalaxy.getPlayer(playerId);
    Player* otherPlayer = gameGalaxy.getPlayer(otherPlayerId);
    if (player != nullptr && otherPlayer != nullptr) {
        double diplomaticInfluence = calculateDiplomaticInfluence(player, otherPlayer);
        updateDiplomacyStatus(player, otherPlayer, diplomaticInfluence);
        applyDiplomacyEffects(player, otherPlayer);
    }
}

// Player class implementation
Player::Player(int playerNumber, const std::string& playerName, double temperaturePreference, double gravityPreference)
    : playerNumber(playerNumber), playerName(playerName), temperaturePreference(temperaturePreference),
      gravityPreference(gravityPreference), totalPopulation(0), totalFundsAccumulated(0.0),
      totalFundsInBank(0.0), totalGrossIncomePerTurn(0.0), totalFundsSpentOnTechnology(0.0),
      numberOfShipsOwned(0), researchPoints(0) {
    technologyLevels = new std::vector<int>();
    planetsOwned = new std::vector<int>();
    planetsSeen = new std::vector<int>();
    propertiesSeenInPossessionOfOtherPlayer = new std::vector<int>();
    diplomacyStatus = new std::vector<int>();
}

Player::~Player() {
    delete technologyLevels;
    delete planetsOwned;
    delete planetsSeen;
    delete propertiesSeenInPossessionOfOtherPlayer;
    delete diplomacyStatus;
}

void Player::updateTotalPopulation() {
    totalPopulation = 0;
    for (int planetId : *planetsOwned) {
        totalPopulation += gameGalaxy.getPlanet(planetId)->getPopulation();
    }
}

void Player::updateTotalFunds() {
    totalFundsAccumulated += totalGrossIncomePerTurn;
    totalFundsInBank = totalFundsAccumulated - totalFundsSpentOnTechnology;
}

void Player::updateGrossIncome() {
    totalGrossIncomePerTurn = 0.0;
    for (int planetId : *planetsOwned) {
        totalGrossIncomePerTurn += gameGalaxy.getPlanet(planetId)->getIncome();
    }
}

void Player::investInTechnology(int technologyIndex, double funds) {
    if (funds <= totalFundsInBank) {
        totalFundsSpentOnTechnology += funds;
        totalFundsInBank -= funds;
        gameGalaxy.getTechnology(technologyIndex)->addResearchPoints(funds);
    }
}

void Player::addPlanetOwned(int planetId) {
    planetsOwned->push_back(planetId);
}

void Player::addPlanetSeen(int planetId) {
    planetsSeen->push_back(planetId);
}

void Player::addPropertySeenInPossessionOfOtherPlayer(int propertyId) {
    propertiesSeenInPossessionOfOtherPlayer->push_back(propertyId);
}

void Player::updateDiplomacyStatus(int playerNumber, int status) {
    if (playerNumber >= 0 && playerNumber < diplomacyStatus->size()) {
        diplomacyStatus->at(playerNumber) = status;
    }
}

void Player::buildShip(int planetId, int shipType) {
    Planet* planet = gameGalaxy.getPlanet(planetId);
    if (planet != nullptr) {
        planet->buildShip(shipType);
        ++numberOfShipsOwned;
    }
}

void Player::update(double deltaTime) {
    updateResourceGeneration(deltaTime);
    updateResearchProgress(deltaTime);
    updateShipProduction(deltaTime);
    updateShipMaintenance(deltaTime);
    updateDiplomacy(deltaTime);
    updateEspionage(deltaTime);
}

void Player::updateResourceGeneration(double deltaTime) {
    double metalGeneration = calculateMetalGeneration(planetsOwned);
    double energyGeneration = calculateEnergyGeneration(planetsOwned);
    double foodGeneration = calculateFoodGeneration(planetsOwned);
    metal += metalGeneration * deltaTime;
    energy += energyGeneration * deltaTime;
    food += foodGeneration * deltaTime;
}

void Player::updateResearchProgress(double deltaTime) {
    for (int i = 0; i < technologies.size(); ++i) {
        double researchProgress = calculateResearchProgress(technologies[i], researchPoints[i], deltaTime);
        technologies[i].addResearchProgress(researchProgress);
        if (technologies[i].isResearched()) {
            applyTechnologyEffects(technologies[i]);
        }
    }
}

void Player::updateShipProduction(double deltaTime) {
    for (int i = 0; i < planets.size(); ++i) {
        int shipProduction = calculateShipProduction(planets[i]);
        planets[i].addShipProductionProgress(shipProduction * deltaTime);
        while (planets[i].isShipCompleted()) {
            Ship newShip = createShip(planets[i].getCompletedShipType());
            ships.push_back(newShip);
            planets[i].removeCompletedShip();
        }
    }
}

void Player::updateShipMaintenance(double deltaTime) {
    for (int i = 0; i < ships.size(); ++i) {
        double maintenanceCost = calculateShipMaintenanceCost(ships[i]);
        deductResources(maintenanceCost);
        applyShipMaintenanceEffects(ships[i], deltaTime);
    }
}

void Player::updateDiplomacy(double deltaTime) {
    for (int i = 0; i < diplomacyStatus.size(); ++i) {
        updateDiplomacyStatus(i, deltaTime);
        applyDiplomacyEffects(i, deltaTime);
    }
}

void Player::updateEspionage(double deltaTime) {
    for (int i = 0; i < espionageMissions.size(); ++i) {
        updateEspionageMissionProgress(espionageMissions[i], deltaTime);
        if (espionageMissions[i].isCompleted()) {
            applyEspionageMissionEffects(espionageMissions[i]);
            espionageMissions.erase(espionageMissions.begin() + i);
            --i;
        }
    }
}

// GameUI class implementation
void GameUI::displayShipInfo(int shipId) {
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

void GameUI::displayTechnologyInfo(int techIndex) {
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

void GameUI::displayPlayerInfo(int playerNumber) {
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

// GameLogic class implementation
void GameLogic::terraformPlanet(int planetId, int targetTemp, double targetGravity) {
    Planet* planet = gameGalaxy.getPlanet(planetId);
    if (planet != nullptr) {
        double tempProgress = calculateTerraformingProgress(planet->getTemperature(), targetTemp);
        double gravityProgress = calculateTerraformingProgress(planet->getGravity(), targetGravity);
        planet->setTemperature(planet->getTemperature() + tempProgress);
        planet->setGravity(planet->getGravity() + gravityProgress);
        applyTerraformingEffects(planet);
    }
}

void GameLogic::conductMining(int planetId) {
    Planet* planet = gameGalaxy.getPlanet(planetId);
    if (planet != nullptr) {
        double miningYield = calculateMiningYield(planet->getMetal(), planet->getMiningLevel());
        planet->setMetal(planet->getMetal() - miningYield);
        applyMiningEffects(planet, miningYield);
    }
}

void GameLogic::performShipMaintenance(int playerId) {
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

void GameLogic::engageInDiplomacy(int playerId, int otherPlayerId) {
    Player* player = gameGalaxy.getPlayer(playerId);
    Player* otherPlayer = gameGalaxy.getPlayer(otherPlayerId);
    if (player != nullptr && otherPlayer != nullptr) {
        double diplomaticInfluence = calculateDiplomaticInfluence(player, otherPlayer);
        updateDiplomacyStatus(player, otherPlayer, diplomaticInfluence);
        applyDiplomacyEffects(player, otherPlayer);
    }
}

void GameLogic::colonizePlanet(Player& player, Planet& planet) {
    if (isPlanetSuitable(player, planet)) {
        establishColony(player, planet);
        planet.setPlayerOwner(player.getPlayerNumber());
        planet.setPopulation(initialColonyPopulation);
        applyColonizationEffects(player, planet);
    }
}

void GameLogic::developPlanet(Player& player, Planet& planet) {
    allocateDevelopmentResources(player, planet);
    updateInfrastructure(planet);
    updateProduction(planet);
    updateDefenses(planet);
    applyDevelopmentEffects(player, planet);
}

void GameLogic::conductEspionage(Player& player, Player& targetPlayer) {
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

void GameLogic::conductSabotage(Player& player, Player& targetPlayer) {
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

// SaveGame class implementation
void SaveGame::saveGameState(const std::string& filename) {
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

void SaveGame::loadGameState(const std::string& filename) {
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

// Galaxy class implementation
void Galaxy::updateGameState(double deltaTime) {
    for (int i = 0; i < planets.size(); ++i) {
        planets[i].update(deltaTime);
    }

    for (int i = 0; i < players.size(); ++i) {
        players[i].update(deltaTime);
    }

    for (int i = 0; i < ships.size(); ++i) {
        ships[i].update(deltaTime);
    }

    updateDiplomacy(deltaTime);
    updateTrade(deltaTime);
    updateResearch(deltaTime);
    updateCombat(deltaTime);
}

void Galaxy::updateDiplomacy(double deltaTime) {
    for (int i = 0; i < players.size(); ++i) {
        for (int j = i + 1; j < players.size(); ++j) {
            double influence = calculateDiplomaticInfluence(players[i], players[j]);
            updateDiplomacyStatus(players[i], players[j], influence);
            applyDiplomacyEffects(players[i], players[j], deltaTime);
        }
    }
}

void Galaxy::updateTrade(double deltaTime) {
    for (int i = 0; i < players.size(); ++i) {
        for (int j = 0; j < players.size(); ++j) {
            if (i != j) {
                double tradePotential = calculateTradePotential(players[i], players[j]);
                establishTradeRoute(players[i], players[j], tradePotential);
                exchangeResources(players[i], players[j], tradePotential, deltaTime);
            }
        }
    }
}

void Galaxy::updateResearch(double deltaTime) {
    for (int i = 0; i < players.size(); ++i) {
        allocateResearchPoints(players[i]);

        for (int j = 0; j < players[i].getNumTechnologies(); ++j) {
            updateResearchProgress(players[i], j, deltaTime);
        }

        checkTechnologyCompletion(players[i]);
    }
}

void Galaxy::updateCombat(double deltaTime) {
    for (int i = 0; i < ships.size(); ++i) {
        for (int j = i + 1; j < ships.size(); ++j) {
            if (isInCombatRange(ships[i], ships[j])) {
                int outcome = calculateCombatOutcome(ships[i], ships[j]);
                applyCombatEffects(ships[i], ships[j], outcome, deltaTime);
            }
        }
    }
}

// AI class implementation
void AI::update(double deltaTime) {
    updateObservableGameState();
    makeDecisions();
    executeActions(deltaTime);
}

void AI::updateObservableGameState() {
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

void AI::makeDecisions() {
    analyzeObservableGameState();
    updateInternalState();
}

void AI::executeActions(double deltaTime) {
    updateGameState(deltaTime);
}

void AI::decidePlanetaryDevelopment() {
    for (Planet* planet : ownedPlanets) {
        double developmentPriority = assessPlanetPotential(planet);
        allocateResourcesForDevelopment(planet, developmentPriority);
        planPlanetaryDevelopment(planet, developmentPriority);
    }
}

void AI::decideFleetMovement() {
    for (Fleet* fleet : ownedFleets) {
        double movementPriority = assessFleetObjectives(fleet);
        planFleetMovement(fleet, movementPriority);
    }
}

void AI::decideResearch() {
    for (Technology* technology : availableTechnologies) {
        double researchPriority = assessTechnologyPotential(technology);
        allocateResearchPoints(technology, researchPriority);
    }
}

void AI::decideDiplomacy() {
    for (Player* player : players) {
        if (player != aiPlayer) {
            double diplomaticPriority = assessDiplomaticStance(player);
            planDiplomaticActions(player, diplomaticPriority);
        }
    }
}

void AI::developPlanets() {
    for (Planet* planet : ownedPlanets) {
        constructInfrastructure(planet);
        allocateResources(planet);
        managePopulation(planet);
    }
}

void AI::moveFleets() {
    for (Fleet* fleet : ownedFleets) {
        moveFleetToTarget(fleet);
        engageInCombat(fleet);
    }
}

void AI::conductResearch() {
    for (Technology* technology : availableTechnologies) {
        allocateResearchPoints(technology);
        updateResearchProgress(technology);
    }
}

void AI::engageInDiplomacy() {
    for (Player* player : players) {
        if (player != aiPlayer) {
            proposeTreaty(player);
            proposeTradeAgreement(player);
            declareWar(player);
        }
    }
}

// GameEvent class implementation
void GameEvent::trigger() {
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

void GameEvent::applyRandomEventEffects() {
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

void GameEvent::displayStoryEventMessage() {
    std::cout << "A story event has occurred: " << eventMessage << std::endl;
}

void GameEvent::displayStoryEventChoices() {
    std::cout << "Choose an action:" << std::endl;
    for (int i = 0; i < choices.size(); ++i) {
        std::cout << i + 1 << ". " << choices[i] << std::endl;
    }
}

void GameEvent::handlePlayerChoice() {
    int choice;
    std::cin >> choice;
    applyChoiceEffects(choice);
}

void GameEvent::initiateDiplomaticNegotiations() {
    displayNegotiationOptions();
    handleNegotiationChoices();
}

void GameEvent::triggerDiplomaticActions() {
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

// BattleSystem class implementation
void BattleSystem::initiateBattle(Player& attacker, Player& defender, Planet& battlePlanet) {
    this->attacker = &attacker;
    this->defender = &defender;
    this->battlePlanet = &battlePlanet;
    
    prepareShipsForBattle(attacker, attackerShips);
    prepareShipsForBattle(defender, defenderShips);

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
    std::cout << "Summary of battle at " << battlePlanet->getName() << " in " << gameGalaxy.getCurrentYear() << ":" << std::endl;
    std::cout << attacker->getName() << " vs. " << defender->getName() << std::endl;
    std::cout << "Round " << round << std::endl;

    displayShipStatus(attackerShips);
    displayShipStatus(defenderShips);

    displayBattleOutcome();
}

void BattleSystem::performBattleRound() {
    for (Ship* ship : attackerShips) {
        performShipAction(ship, defenderShips);
    }

    for (Ship* ship : defenderShips) {
        performShipAction(ship, attackerShips);
    }

    removeDestroyedShips(attackerShips);
    removeDestroyedShips(defenderShips);
}

void BattleSystem::displayRoundSummary() {
    std::cout << "Round " << round << " summary:" << std::endl;

    displayShipActions(attackerShips);
    displayShipActions(defenderShips);
}

void BattleSystem::determineBattleOutcome() {
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

void BattleSystem::resolveBattleVictory(Player& victor, Planet& planet) {
    planet.setOwner(victor);
    applyBattleEffects(victor, planet);
    awardBattleRewards(victor, planet);
}

void BattleSystem::prepareShipsForBattle(Player& player, std::vector<Ship*>& ships) {
    for (Ship* ship : player.getFleet()) {
        if (ship->isReadyForBattle()) {
            ships.push_back(ship);
        }
    }
}

void BattleSystem::performShipAction(Ship* ship, std::vector<Ship*>& enemyShips) {
    Ship* target = selectTarget(enemyShips);
    ship->performAction(target);
}

void BattleSystem::removeDestroyedShips(std::vector<Ship*>& ships) {
    ships.erase(std::remove_if(ships.begin(), ships.end(), [](Ship* ship) { return ship->isDestroyed(); }), ships.end());
}

void BattleSystem::displayShipStatus(const std::vector<Ship*>& ships) {
    for (Ship* ship : ships) {
        std::cout << ship->getName() << " (" << ship->getHullStrength() << "/" << ship->getMaxHullStrength() << ")" << std::endl;
    }
}

void BattleSystem::displayShipActions(const std::vector<Ship*>& ships) {
    for (Ship* ship : ships) {
        std::cout << ship->getName() << " performs " << ship->getLastAction() << std::endl;
    }
}

void BattleSystem::applyBattleEffects(Player& victor, Planet& planet) {
    planet.applyBattleDamage();
    planet.applyPopulationLoss();

    for (Ship* ship : victor.getFleet()) {
        ship->gainExperience();
        ship->applyUpgrades();
    }
}

void BattleSystem::awardBattleRewards(Player& victor, Planet& planet) {
    victor.addResources(planet.getResourceReward());
    victor.addTechnology(planet.getTechnologyReward());
    victor.addReputation(planet.getReputationReward());
}

Ship* BattleSystem::selectTarget(const std::vector<Ship*>& enemyShips) {
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

bool BattleSystem::isBattleOver() {
    return attackerShips.empty() || defenderShips.empty();
}

// Game class implementation
void Game::run() {
    while (!isGameOver) {
        gameGalaxy.update(deltaTime);

        for (Player* player : players) {
            player->update(deltaTime);
        }

        for (AI* aiPlayer : aiPlayers) {
            aiPlayer->update(deltaTime);
        }

        handleEvents();
        triggerEvents();

        checkVictoryConditions();

        renderGraphics();
    }
}

void Game::initiateBattle(Player& attacker, Player& defender, Planet& planet) {
    BattleSystem battleSystem(gameGalaxy);
    battleSystem.initiateBattle(attacker, defender, planet);
    battleSystem.simulateBattle();
    battleSystem.displayBattleSummary();
}

void Game::handleEvents() {
    for (GameEvent* event : activeEvents) {
        event->handleEvent();
        updateGameState(event);
    }
}

void Game::triggerEvents() {
    triggerRandomEvents();
    triggerStoryEvents();
    triggerDiplomaticEvents();
}

void Game::checkVictoryConditions() {
    for (Player* player : players) {
        if (player->hasAchievedVictory()) {
            isGameOver = true;
            declareWinner(player);
            break;
        }
    }
}

void Game::renderGraphics() {
    renderGalaxyMap();
    renderPlayerInterfaces();
    renderBattleVisualizations();
}

int main() {
    Game game;
    game.run();
    return 0;
}

// Calculation methods
double calculatePopulationGrowth(double currentPopulation, double growthRate, double carryingCapacity) {
    return currentPopulation * growthRate * (1 - currentPopulation / carryingCapacity);
}

double calculateResourceProduction(double baseProduction, double productionMultiplier, double productionBonus) {
    return baseProduction * productionMultiplier + productionBonus;
}

double calculateShipMaintenanceCost(const Ship& ship) {
    double baseMaintenanceCost = 100.0;
    double maintenanceMultiplier = 1.0 + ship.getUpgradeLevel() * 0.1;
    return baseMaintenanceCost * maintenanceMultiplier;
}

double calculateResearchProgress(double currentProgress, double researchRate, double researchMultiplier) {
    return currentProgress + researchRate * researchMultiplier;
}

double calculateCombatDamage(double attackerWeapon, double defenderArmor) {
    double baseDamage = 50.0;
    double damageMultiplier = attackerWeapon / (attackerWeapon + defenderArmor);
    return baseDamage * damageMultiplier;
}

double calculateExperienceGain(double baseExperience, double experienceMultiplier) {
    return baseExperience * experienceMultiplier;
}

double calculateDiplomaticInfluence(double currentInfluence, double influenceGain, double decayRate) {
    return currentInfluence + influenceGain - currentInfluence * decayRate;
}

double calculateTradeProfit(double baseProfitPerUnit, int quantityTraded, double profitMultiplier) {
    return baseProfitPerUnit * quantityTraded * profitMultiplier;
}

double calculateShipSpeed(double baseSpeed, double speedMultiplier, double speedBonus) {
    return baseSpeed * speedMultiplier + speedBonus;
}

double calculateSensorRange(double baseSensorRange, double sensorRangeMultiplier, double sensorRangeBonus) {
    return baseSensorRange * sensorRangeMultiplier + sensorRangeBonus;
}

double calculateTerraformingProgress(double currentProgress, double terraformingRate, double terraformingMultiplier) {
    return currentProgress + terraformingRate * terraformingMultiplier;
}

double calculateMiningYield(double baseMiningYield, double miningEfficiency, double miningBonus) {
    return baseMiningYield * miningEfficiency + miningBonus;
}

double calculateEspionageSuccessProbability(double espionageSkill, double targetSecurity) {
    double baseSuccessProbability = 0.5;
    double probabilityMultiplier = espionageSkill / (espionageSkill + targetSecurity);
    return baseSuccessProbability * probabilityMultiplier;
}

double calculateSabotageSuccessProbability(double sabotageSkill, double targetSecurity) {
    double baseSuccessProbability = 0.3;
    double probabilityMultiplier = sabotageSkill / (sabotageSkill + targetSecurity);
    return baseSuccessProbability * probabilityMultiplier;
}

double calculateRandomEventProbability(double eventFrequency) {
    return eventFrequency / 100.0;
}

double calculateVictoryPoints(int planetsOwned, int populationTotal, double technologyLevel, double militaryStrength, double diplomaticInfluence) {
    double planetPoints = planetsOwned * 10.0;
    double populationPoints = populationTotal * 0.01;
    double technologyPoints = technologyLevel * 5.0;
    double militaryPoints = militaryStrength * 3.0;
    double diplomaticPoints = diplomaticInfluence * 2.0;
    return planetPoints + populationPoints + technologyPoints + militaryPoints + diplomaticPoints;
}

// Update methods for various game entities
void Galaxy::updatePlanets(double deltaTime) {
    for (Planet& planet : planets) {
        planet.update(deltaTime);
    }
}

void Galaxy::updateShips(double deltaTime) {
    for (Ship& ship : ships) {
        ship.update(deltaTime);
    }
}

void Galaxy::updatePlayers(double deltaTime) {
    for (Player& player : players) {
        player.update(deltaTime);
    }
}

void Galaxy::updateTechnologies(double deltaTime) {
    for (Technology& technology : technologies) {
        technology.update(deltaTime);
    }
}

void Galaxy::updateGameEvents(double deltaTime) {
    for (GameEvent& event : gameEvents) {
        event.update(deltaTime);
    }
}

void Planet::updatePopulation(double deltaTime) {
    population += calculatePopulationGrowth(population, deltaTime);
}

void Planet::updateResources(double deltaTime) {
    resources += calculateResourceProduction(resources, deltaTime);
}

void Planet::updateInfrastructure(double deltaTime) {
    infrastructure += calculateInfrastructureGrowth(infrastructure, deltaTime);
}

void Planet::updateDefenses(double deltaTime) {
    defense += calculateDefenseImprovement(defense, deltaTime);
}

void Planet::updateTerraforming(double deltaTime) {
    terraformingProgress += calculateTerraformingProgress(terraformingProgress, deltaTime);
}

void Planet::updateMining(double deltaTime) {
    miningProgress += calculateMiningProgress(miningProgress, deltaTime);
}

void Ship::updatePosition(double deltaTime) {
    position += velocity * deltaTime;
}

void Ship::updateFuel(double deltaTime) {
    fuel -= calculateFuelConsumption(velocity, deltaTime);
}

void Ship::updateHealth(double deltaTime) {
    health = std::min(health + calculateRepairRate(health, deltaTime), maxHealth);
}

void Ship::updateWeapons(double deltaTime) {
    weaponCooldown = std::max(weaponCooldown - deltaTime, 0.0);
}

void Ship::updateShields(double deltaTime) {
    shields = std::min(shields + calculateShieldRegeneration(shields, deltaTime), maxShields);
}

void Player::updateResourceIncome(double deltaTime) {
    resourceIncome = calculateResourceIncome(ownedPlanets, deltaTime);
}

void Player::updateResearchProgress(double deltaTime) {
    for (Technology& technology : researchedTechnologies) {
        technology.update(deltaTime);
    }
}

void Player::updateDiplomacy(double deltaTime) {
    for (Player& otherPlayer : diplomacyStatus) {
        updateDiplomaticRelations(otherPlayer, deltaTime);
    }
}

void Player::updateFleet(double deltaTime) {
    for (Ship& ship : ownedShips) {
        ship.update(deltaTime);
    }
}

void Technology::updateResearchProgress(double deltaTime) {
    researchProgress += calculateResearchProgress(researchProgress, deltaTime);
    if (researchProgress >= requiredResearch) {
        isResearched = true;
        applyTechnologyEffects();
    }
}

void GameEvent::updateEventTimer(double deltaTime) {
    eventTimer -= deltaTime;
    if (eventTimer <= 0.0) {
        triggerEvent();
    }
}

void AI::updateObservableGameState() {
    // Update observable planets, ships, players, technologies, and game events
    observablePlanets = getVisiblePlanets();
    observableShips = getVisibleShips();
    observablePlayers = getVisiblePlayers();
    observableTechnologies = getVisibleTechnologies();
    observableGameEvents = getVisibleGameEvents();
}

void AI::makeDecisions() {
    analyzeObservableGameState();
    makeStrategicDecisions();
    updateInternalState();
}

void AI::executeActions(double deltaTime) {
    executePlanetaryDevelopmentActions(deltaTime);
    executeFleetMovementActions(deltaTime);
    executeResearchActions(deltaTime);
    executeDiplomacyActions(deltaTime);
}

// MCTS (Monte Carlo Tree Search) implementation
class MCTS {
public:
    struct Node {
        GameState state;
        std::vector<Node*> children;
        int visits;
        double totalReward;
    };

    Node* root;

    MCTS(const GameState& initialState) {
        root = new Node{initialState, {}, 0, 0.0};
    }

    Action selectBestAction(int numSimulations) {
        for (int i = 0; i < numSimulations; ++i) {
            Node* node = treePolicy(root);
            double reward = defaultPolicy(node->state);
            backpropagate(node, reward);
        }
        return bestChild(root)->state.getLastAction();
    }

private:
    Node* treePolicy(Node* node) {
        while (!node->state.isTerminal()) {
            if (!node->state.isFullyExpanded()) {
                return expand(node);
            } else {
                node = bestChild(node);
            }
        }
        return node;
    }

    Node* expand(Node* node) {
        Action action = node->state.getUntriedAction();
        GameState nextState = node->state.getNextState(action);
        Node* childNode = new Node{nextState, {}, 0, 0.0};
        node->children.push_back(childNode);
        return childNode;
    }

    Node* bestChild(Node* node) {
        double bestScore = -std::numeric_limits<double>::infinity();
        Node* bestNode = nullptr;
        for (Node* child : node->children) {
            double score = child->totalReward / child->visits + sqrt(2 * log(node->visits) / child->visits);
            if (score > bestScore) {
                bestScore = score;
                bestNode = child;
            }
        }
        return bestNode;
    }

    double defaultPolicy(GameState state) {
        while (!state.isTerminal()) {
            Action action = state.getRandomAction();
            state = state.getNextState(action);
        }
        return state.getReward();
    }

    void backpropagate(Node* node, double reward) {
        while (node != nullptr) {
            node->visits++;
            node->totalReward += reward;
            node = node->parent;
        }
    }
};

// Genetic Algorithm implementation
class GeneticAlgorithm {
public:
    struct Individual {
        std::vector<double> genes;
        double fitness;
    };

    std::vector<Individual> population;
    int populationSize;
    double crossoverRate;
    double mutationRate;

    GeneticAlgorithm(int populationSize, double crossoverRate, double mutationRate)
        : populationSize(populationSize), crossoverRate(crossoverRate), mutationRate(mutationRate) {
        initializePopulation();
    }

    std::vector<double> findBestSolution(int numGenerations) {
        for (int i = 0; i < numGenerations; ++i) {
            std::vector<Individual> newPopulation;
            for (int j = 0; j < populationSize; ++j) {
                Individual parent1 = selection();
                Individual parent2 = selection();
                Individual offspring = crossover(parent1, parent2);
                mutate(offspring);
                newPopulation.push_back(offspring);
            }
            population = newPopulation;
        }
        return getBestIndividual().genes;
    }

private:
    void initializePopulation() {
        for (int i = 0; i < populationSize; ++i) {
            Individual individual;
            individual.genes = generateRandomSolution();
            individual.fitness = evaluateFitness(individual.genes);
            population.push_back(individual);
        }
    }

    std::vector<double> generateRandomSolution() {
        // Generate a random solution (genes) for the problem
    }

    double evaluateFitness(const std::vector<double>& genes) {
        // Evaluate the fitness of the solution (genes)
    }

    Individual selection() {
        // Select an individual from the population based on fitness
    }

    Individual crossover(const Individual& parent1, const Individual& parent2) {
        // Perform crossover between two parent individuals to create an offspring
    }

    void mutate(Individual& individual) {
        // Mutate the genes of an individual with a certain probability
    }

    Individual getBestIndividual() {
        Individual bestIndividual = population[0];
        for (const Individual& individual : population) {
            if (individual.fitness > bestIndividual.fitness) {
                bestIndividual = individual;
            }
        }
        return bestIndividual;
    }
};

// Q-Learning implementation
class QLearning {
public:
    std::unordered_map<State, std::unordered_map<Action, double>> qTable;
    double learningRate;
    double discountFactor;
    double explorationRate;

    QLearning(double learningRate, double discountFactor, double explorationRate)
        : learningRate(learningRate), discountFactor(discountFactor), explorationRate(explorationRate) {}

    void learn(const State& state, const Action& action, double reward, const State& nextState) {
        double maxQNextState = getMaxQValue(nextState);
        double qValue = qTable[state][action];
        double newQValue = qValue + learningRate * (reward + discountFactor * maxQNextState - qValue);
        qTable[state][action] = newQValue;
    }

    Action selectAction(const State& state) {
        if (randomDouble() < explorationRate) {
            return getRandomAction(state);
        } else {
            return getMaxQAction(state);
        }
    }

private:
    double getMaxQValue(const State& state) {
        double maxValue = -std::numeric_limits<double>::infinity();
        for (const auto& entry : qTable[state]) {
            double qValue = entry.second;
            if (qValue > maxValue) {
                maxValue = qValue;
            }
        }
        return maxValue;
    }

    Action getMaxQAction(const State& state) {
        double maxValue = -std::numeric_limits<double>::infinity();
        Action maxAction;
        for (const auto& entry : qTable[state]) {
            Action action = entry.first;
            double qValue = entry.second;
            if (qValue > maxValue) {
                maxValue = qValue;
                maxAction = action;
            }
        }
        return maxAction;
    }

    double randomDouble() {
        return static_cast<double>(rand()) / RAND_MAX;
    }

    Action getRandomAction(const State& state) {
        // Get a random action for the given state
    }
};

// HTN (Hierarchical Task Network) Planner implementation
class HTNPlanner {
public:
    struct Task {
        std::string name;
        std::vector<std::shared_ptr<Task>> subtasks;
    };

    struct Method {
        std::string taskName;
        std::function<bool(const GameState&)> precondition;
        std::vector<std::shared_ptr<Task>> decomposition;
    };

    std::vector<Method> methods;

    std::vector<std::shared_ptr<Task>> plan(const GameState& state, const std::shared_ptr<Task>& task) {
        if (task->subtasks.empty()) {
            return {task};
        }
        for (const auto& method : methods) {
            if (method.taskName == task->name && method.precondition(state)) {
                std::vector<std::shared_ptr<Task>> subplan;
                for (const auto& subtask : method.decomposition) {
                    auto subsubplan = plan(state, subtask);
                    subplan.insert(subplan.end(), subsubplan.begin(), subsubplan.end());
                }
                if (!subplan.empty()) {
                    return subplan;
                }
            }
        }
        return {};
    }
};

// Utility functions
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

double randomDouble(double min, double max) {
    return min + (max - min) * (static_cast<double>(rand()) / RAND_MAX);
}

bool isInRange(double value, double min, double max) {
    return value >= min && value <= max;
}

// Resource management
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

// Ship management
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

void Ship::moveToTarget(const Position& target, double deltaTime) {
    double distance = calculateDistance(position.x, position.y, target.x, target.y);
    if (distance > 0.0) {
        double angle = calculateAngle(position.x, position.y, target.x, target.y);
        double rotationAngle = calculateRotationAngle(rotation, angle);
        rotate(rotationAngle * rotationSpeed * deltaTime);
        double movementDistance = std::min(distance, speed * deltaTime);
        position.x += std::cos(rotation) * movementDistance;
        position.y += std::sin(rotation) * movementDistance;
    }
}

void Ship::attackTarget(Ship* target, double deltaTime) {
    if (target != nullptr) {
        double distance = calculateDistance(position.x, position.y, target->getPosition().x, target->getPosition().y);
        if (distance <= weaponRange) {
            double damage = calculateWeaponDamage();
            target->takeDamage(damage);
            weaponCooldown = weaponReloadTime;
        } else {
            moveToTarget(target->getPosition(), deltaTime);
        }
    }
}

void Ship::defendPosition(const Position& position, double deltaTime) {
    double distance = calculateDistance(this->position.x, this->position.y, position.x, position.y);
    if (distance > defenseRange) {
        moveToTarget(position, deltaTime);
    }
}

// Planet management
void Player::colonizePlanet(Planet* planet) {
    if (planet->getOwner() == nullptr && canAfford(getColonizationCost(planet))) {
        consumeResources(getColonizationCost(planet));
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

// Technology research
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
    if (!isResearched) {
        researchProgress += player->getResearchOutput();
        if (researchProgress >= researchCost) {
            isResearched = true;
            applyEffects(player);
        }
    }
}

void Technology::applyEffects(Player* player) {
    // Apply technology effects to the player
    if (name == "Improved Mining") {
        for (Planet* planet : player->getOwnedPlanets()) {
            planet->miningEfficiency *= 1.1;
        }
    } else if (name == "Advanced Energy") {
        for (Planet* planet : player->getOwnedPlanets()) {
            planet->energyEfficiency *= 1.1;
        }
    } else if (name == "Faster Ships") {
        for (Ship* ship : player->getOwnedShips()) {
            ship->speed *= 1.2;
        }
    }
}

// Diplomacy and trade
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
}

bool Player::evaluateTradeOffer(const TradeOffer& offer) {
    // Evaluate the trade offer based on player's trade strategy and current needs
    return true;
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

void Player::rejectAlliance(Player* otherPlayer) {
    // Reject the alliance proposal
}

bool Player::evaluateAllianceProposal(Player* sender) {
    // Evaluate the alliance proposal based on player's diplomatic strategy and relationship with the sender
    return true;
}

void Player::receiveWarDeclaration(Player* sender) {
    // Handle the war declaration
    enemies.push_back(sender);
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

void Player::rejectPeace(Player* otherPlayer) {
    // Reject the peace proposal
}

bool Player::evaluatePeaceProposal(Player* sender) {
    // Evaluate the peace proposal based on player's diplomatic strategy and current relationship with the sender
    return true;
}

void Player::removeEnemy(Player* enemy) {
    enemies.erase(std::remove(enemies.begin(), enemies.end(), enemy), enemies.end());
}

// Event system
void GameEvent::trigger() {
    // Trigger the game event
}

void GameEvent::applyEffects() {
    // Apply the effects of the game event
}

void GameEvent::revert() {
    // Revert the effects of the game event
}

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

void GameState::applyEventEffects() {
    for (GameEvent* event : events) {
        event->applyEffects();
    }
}

void GameState::revertEventEffects() {
    for (GameEvent* event : events) {
        event->revert();
    }
}

// Save/Load system
void GameState::save(const std::string& filename) {
    // Save the game state to a file
}

void GameState::load(const std::string& filename) {
    // Load the game state from a file
}

// Input handling
void GameState::handleInput() {
    // Handle player input
}

void GameState::handleKeyPress(const sf::Event::KeyEvent& event) {
    // Handle key press event
}

void GameState::handleMouseClick(const sf::Event::MouseButtonEvent& event) {
    // Handle mouse click event
}

// Game loop
void GameState::update(double deltaTime) {
    // Update game state
    updatePlanets(deltaTime);
    updateShips(deltaTime);
    updatePlayers(deltaTime);
    updateTechnologies(deltaTime);
    updateGameEvents(deltaTime);
    triggerEvents();
    applyEventEffects();
    handleInput();
}

void GameState::render() {
    // Render game graphics
    renderGalaxy();
    renderPlanets();
    renderShips();
    renderPlayers();
    renderUI();
}

void runGame() {
    GameState gameState;
    sf::RenderWindow window(sf::VideoMode(1024, 768), "Spaceward Ho!");
    sf::Clock clock;

    while (window.isOpen()) {
        double deltaTime = clock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed) {
                gameState.handleKeyPress(event.key);
            } else if (event.type == sf::Event::MouseButtonPressed) {
                gameState.handleMouseClick(event.mouseButton);
            }
        }

        gameState.update(deltaTime);

        window.clear();
        gameState.render();
        window.display();
    }
}

int main() {
    runGame();
    return 0;
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
    // Remove the ship from the game
    isDestroyed = true;
}

double Ship::calculateWeaponDamage() {
    return weaponDamage;
}

void Ship::rotate(double angle) {
    rotation += angle;
    if (rotation > 2 * M_PI) {
        rotation -= 2 * M_PI;
    } else if (rotation < 0) {
        rotation += 2 * M_PI;
    }
}

double getColonizationCost(Planet* planet) {
    return planet->getColonizationCost();
}

double Player::getResearchOutput() {
    double researchOutput = 0.0;
    for (Planet* planet : ownedPlanets) {
        researchOutput += planet->getResearchOutput();
    }
    return researchOutput;
}

double Player::getTechMetalCost(const std::string& techName) {
    Technology* tech = gameState->getTechnology(techName);
    if (tech != nullptr) {
        return tech->getMetalCost();
    }
    return 0.0;
}

double Player::getTechEnergyCost(const std::string& techName) {
    Technology* tech = gameState->getTechnology(techName);
    if (tech != nullptr) {
        return tech->getEnergyCost();
    }
    return 0.0;
}

void GameState::renderGalaxy() {
    // Render the galaxy background
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Render stars
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (const auto& star : stars) {
        SDL_RenderDrawPoint(renderer, star.x, star.y);
    }

    // Render planets
    for (Planet* planet : planets) {
        planet->render(renderer);
    }

    // Render ships
    for (Ship* ship : ships) {
        ship->render(renderer);
    }
}

void GameState::renderPlanets() {
    for (Planet* planet : planets) {
        planet->render();
    }
}

void GameState::renderShips() {
    for (Ship* ship : ships) {
        ship->render();
    }
}

void GameState::renderPlayers() {
    for (Player* player : players) {
        player->render();
    }
}

void GameState::renderUI() {
    // Render the game UI
}

// Additional classes and functions

class Planet {
public:
    // ...

    double getColonizationCost() {
        return colonizationCost;
    }

    double getResearchOutput() {
        return researchOutput;
    }

    void render(SDL_Renderer* renderer) {
        // Render the planet
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
        SDL_RenderFillCircle(renderer, position.x, position.y, radius);
    }

private:
    double colonizationCost;
    double researchOutput;
};

class Technology {
public:
    // ...

    double getMetalCost() {
        return metalCost;
    }

    double getEnergyCost() {
        return energyCost;
    }

private:
    double metalCost;
    double energyCost;
};

double getShipMetalCost(const std::string& shipType) {
    // Return the metal cost of constructing a ship of the given type
    if (shipType == "Scout") {
        return 10.0;
    } else if (shipType == "Frigate") {
        return 20.0;
    } else if (shipType == "Destroyer") {
        return 30.0;
    } else {
        return 0.0;
    }
}

double getShipEnergyCost(const std::string& shipType) {
    // Return the energy cost of constructing a ship of the given type
    if (shipType == "Scout") {
        return 5.0;
    } else if (shipType == "Frigate") {
        return 10.0;
    } else if (shipType == "Destroyer") {
        return 15.0;
    } else {
        return 0.0;
    }
}

void Player::render(SDL_Renderer* renderer) {
    // Render the player's UI and other visual elements
    // TODO: Implement rendering logic using SDL
}

void runGame() {
    // ...

    // Load initial game state
    if (!gameState.load("initial_state.sav")) {
        // Handle error if loading fails
        std::cerr << "Failed to load initial game state." << std::endl;
        
        // Create a new game state with default values
        gameState = GameState();
        
        // Save the new game state
        if (!gameState.save("initial_state.sav")) {
            std::cerr << "Failed to save initial game state." << std::endl;
            return;
        }
    }

    // ...
}

void Ship::repair(double amount) {
    health = std::min(health + amount, maxHealth);
}

void Ship::refillShields(double amount) {
    shields = std::min(shields + amount, maxShields);
}

void Ship::upgradeWeapons(double damageIncrease) {
    weaponDamage += damageIncrease;
}

void Ship::upgradeShields(double shieldIncrease) {
    maxShields += shieldIncrease;
    shields = maxShields;
}

void Ship::upgradeSpeed(double speedIncrease) {
    speed += speedIncrease;
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


void Technology::applyEffects(Player* player) {
    if (name == "Advanced Mining") {
        for (Planet* planet : player->getOwnedPlanets()) {
            planet->increaseMiningEfficiency(0.1);
        }
    } else if (name == "Energy Efficiency") {
        for (Planet* planet : player->getOwnedPlanets()) {
            planet->increaseEnergyEfficiency(0.1);
        }
    } else if (name == "Weapons Upgrade") {
        for (Ship* ship : player->getOwnedShips()) {
            ship->upgradeWeapons(10.0);
        }
    } else if (name == "Shield Upgrade") {
        for (Ship* ship : player->getOwnedShips()) {
            ship->upgradeShields(50.0);
        }
    } else if (name == "Engine Upgrade") {
        for (Ship* ship : player->getOwnedShips()) {
            ship->upgradeSpeed(1.0);
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

class RandomEvent : public GameEvent {
public:
    RandomEvent(const std::string& name, double probability)
        : GameEvent(name), probability(probability) {}

    void trigger() override {
        if (randomDouble(0.0, 1.0) < probability) {
            applyEffects();
        }
    }

private:
    double probability;
};

class TimedEvent : public GameEvent {
public:
    TimedEvent(const std::string& name, double interval)
        : GameEvent(name), interval(interval), elapsedTime(0.0) {}

    void update(double deltaTime) override {
        elapsedTime += deltaTime;
        if (elapsedTime >= interval) {
            trigger();
            elapsedTime = 0.0;
        }
    }

private:
    double interval;
    double elapsedTime;
};


void GameState::load(const std::string& filename) {
    // Load game state from file
    // ...

    // Create random events
    events.push_back(new RandomEvent("Solar Flare", 0.01));
    events.push_back(new RandomEvent("Asteroid Field", 0.05));
    events.push_back(new RandomEvent("Pirate Attack", 0.03));

    // Create timed events
    events.push_back(new TimedEvent("Resource Boost", 60.0));
    events.push_back(new TimedEvent("Technology Breakthrough", 120.0));
}
class TechnologyBreakthroughEvent : public TimedEvent {
public:
    TechnologyBreakthroughEvent(const std::string& name, double interval)
        : TimedEvent(name, interval) {}

    void trigger() override {
        // Apply the effects of the technology breakthrough event
        // Increase the player's research points
        player.researchPoints += 100;

        // Unlock a random technology
        std::vector<Technology> unlockedTechnologies = player.getUnlockedTechnologies();
        if (!unlockedTechnologies.empty()) {
            int randomIndex = rand() % unlockedTechnologies.size();
            player.unlockTechnology(unlockedTechnologies[randomIndex]);
        }
    }
}
void GameState::update(double deltaTime) {
    // Update game state
    // ...

    // Update events
    for (GameEvent* event : events) {
        event->update(deltaTime);
    }

    // Check for triggered events and handle them
    for (GameEvent* event : events) {
        if (event->isTriggered()) {
            event->handleEvent(this);
            event->reset();
        }
    }
}

class SolarFlareEvent : public RandomEvent {
public:
    SolarFlareEvent() : RandomEvent("Solar Flare", 0.01) {}

    void applyEffects() override {
        for (Planet* planet : gameState->getPlanets()) {
            if (randomDouble(0.0, 1.0) < 0.5) {
                double damage = randomDouble(0.1, 0.3);
                planet->takeDamage(damage);
            }
        }
    }
};

class AsteroidFieldEvent : public RandomEvent {
public:
    AsteroidFieldEvent() : RandomEvent("Asteroid Field", 0.05) {}

    void applyEffects() override {
        for (Ship* ship : gameState->getShips()) {
            if (randomDouble(0.0, 1.0) < 0.3) {
                double damage = randomDouble(0.2, 0.5);
                ship->takeDamage(damage);
            }
        }
    }
};

class PirateAttackEvent : public RandomEvent {
public:
    PirateAttackEvent() : RandomEvent("Pirate Attack", 0.03) {}

    void applyEffects() override {
        for (Player* player : gameState->getPlayers()) {
            if (randomDouble(0.0, 1.0) < 0.5) {
                double stolenResources = player->getResources() * randomDouble(0.1, 0.2);
                player->loseResources(stolenResources);
            }
        }
    }
};

class ResourceBoostEvent : public TimedEvent {
public:
    ResourceBoostEvent() : TimedEvent("Resource Boost", 60.0) {}

    void applyEffects() override {
        for (Planet* planet : gameState->getPlanets()) {
            double boostFactor = randomDouble(1.2, 1.5);
            planet->applyResourceBoost(boostFactor);
        }
    }
};

class TechnologyBreakthroughEvent : public TimedEvent {
public:
    TechnologyBreakthroughEvent() : TimedEvent("Technology Breakthrough", 120.0) {}

    void applyEffects() override {
        for (Player* player : gameState->getPlayers()) {
            Technology* randomTech = gameState->getRandomUnresearchedTechnology();
            if (randomTech != nullptr) {
                randomTech->research(player);
            }
        }
    }
};

void Planet::takeDamage(double damage) {
    health -= damage;
    if (health < 0) {
        health = 0;
    }
    population *= (1.0 - damage / maxHealth);
}

void Planet::applyResourceBoost(double boostFactor) {
    resourceProductionRate *= boostFactor;
    resourceBoostTimer = 60.0;
}

void Player::loseResources(double amount) {
    resources -= amount;
    if (resources < 0) {
        resources = 0;
    }
}

Technology* GameState::getRandomUnresearchedTechnology() {
    std::vector<Technology*> unresearchedTechs;
    for (Technology* tech : technologies) {
        if (!tech->isResearched()) {
            unresearchedTechs.push_back(tech);
        }
    }
    if (!unresearchedTechs.empty()) {
        int randomIndex = rand() % unresearchedTechs.size();
        return unresearchedTechs[randomIndex];
    }
    return nullptr;
}

SDL_Window* window = SDL_CreateWindow("Spaceward Ho!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

SDL_Event event;
while (SDL_PollEvent(&event)) {
    // Handle events
    if (event.type == SDL_QUIT) {
        // Quit the game
    }
    // ...
}


SDL_Rect rect = { x, y, width, height };
SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
SDL_RenderFillRect(renderer, &rect);


SDL_Texture* texture = IMG_LoadTexture(renderer, "texture.png");
SDL_Rect destRect = { x, y, width, height };
SDL_RenderCopy(renderer, texture, NULL, &destRect);


TTF_Font* font = TTF_OpenFont("font.ttf", fontSize);
SDL_Color color = { 255, 255, 255, 255 };
SDL_Surface* surface = TTF_RenderText_Solid(font, "Hello, SDL!", color);
SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
SDL_Rect destRect = { x, y, surface->w, surface->h };
SDL_RenderCopy(renderer, texture, NULL, &destRect);


Mix_Chunk* sound = Mix_LoadWAV("sound.wav");
Mix_PlayChannel(-1, sound, 0);


const Uint8* keyboardState = SDL_GetKeyboardState(NULL);
if (keyboardState[SDL_SCANCODE_SPACE]) {
    // Space key is pressed
}

int mouseX, mouseY;
Uint32 mouseState = SDL_GetMouseState(&mouseX, &mouseY);
if (mouseState & SDL_BUTTON(SDL_BUTTON_LEFT)) {
    // Left mouse button is pressed
}


void runGame() {
    // ...

    SDL_Window* window = SDL_CreateWindow("Spaceward Ho!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Game loop
    bool quit = false;
    while (!quit) {
        double deltaTime = 0.0; // Calculate delta time using SDL_GetTicks()

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            } else if (event.type == SDL_KEYDOWN) {
                // Handle key press event
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                // Handle mouse click event
            }
        }

        gameState.update(deltaTime);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        gameState.render(renderer);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void GameState::render(SDL_Renderer* renderer) {
    // Render game graphics using SDL2 rendering functions
    renderGalaxy(renderer);
    renderPlanets(renderer);
    renderShips(renderer);
    renderPlayers(renderer);
    renderUI(renderer);
}

void GameState::renderGalaxy(SDL_Renderer *renderer)
{
    // Render the galaxy background using SDL2 rendering functions
    // TODO: Implement galaxy rendering logic here

    // Example galaxy rendering logic:
    SDL_SetRenderDrawColor(renderer, 0, 0, 64, 255);
    SDL_Rect galaxyRect = {0, 0, 1024, 768};
    SDL_RenderFillRect(renderer, &galaxyRect);

    // Render stars
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (int i = 0; i < 100; i++)
    {
        int x = rand() % 1024;
        int y = rand() % 768;
        SDL_RenderDrawPoint(renderer, x, y);
    }
}

void GameState::renderPlanets(SDL_Renderer* renderer) {
    for (Planet* planet : planets) {
        planet->render(renderer);
    }
}

void GameState::render(SDL_Renderer* renderer) {
    // Render game graphics using SDL2 rendering functions
    renderGalaxy(renderer);
    renderPlanets(renderer);
    renderShips(renderer);
    renderPlayers(renderer);
    renderUI(renderer);
}
void GameState::renderGalaxy(SDL_Renderer *renderer)
{
    // Render the galaxy background using SDL2 rendering functions
    // TODO: Implement galaxy rendering logic here

    // Example galaxy rendering logic:
    SDL_SetRenderDrawColor(renderer, 0, 0, 64, 255);
    SDL_Rect galaxyRect = {0, 0, 1024, 768};
    SDL_RenderFillRect(renderer, &galaxyRect);

    // Render stars
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (int i = 0; i < 100; i++)
    {
        int x = rand() % 1024;
        int y = rand() % 768;
        SDL_RenderDrawPoint(renderer, x, y);
    }
}

void GameState::renderPlanets(SDL_Renderer* renderer) {
    for (Planet* planet : planets) {
        planet->render(renderer);
    }
}

void GameState::renderGalaxy(SDL_Renderer *renderer)
{
    // Render the galaxy background using SDL2 rendering functions
    // TODO: Implement galaxy rendering logic here

    // Example galaxy rendering logic:
    SDL_SetRenderDrawColor(renderer, 0, 0, 64, 255);
    SDL_Rect galaxyRect = {0, 0, 1024, 768};
    SDL_RenderFillRect(renderer, &galaxyRect);

    // Render stars
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (int i = 0; i < 100; i++)
    {
        int x = rand() % 1024;
        int y = rand() % 768;
        SDL_RenderDrawPoint(renderer, x, y);
    }
}

void GameState::renderPlanets(SDL_Renderer *renderer)
{
    for (Planet *planet : planets)
    {
        planet->render(renderer);
    }
}

void GameState::render(SDL_Renderer *renderer)
{
    // Render game graphics using SDL2 rendering functions
    renderGalaxy(renderer);
    renderPlanets(renderer);
    renderShips(renderer);
    renderPlayers(renderer);
    renderUI(renderer);
}

void runGame()
{
    SDL_Window *window = SDL_CreateWindow("Spaceward Ho!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Game loop
    bool quit = false;
    while (!quit)
    {
        double deltaTime = 0.0; // Calculate delta time using SDL_GetTicks()

        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
            }
            else if (event.type == SDL_KEYDOWN)
            {
                // Handle key press event
                const Uint8 *keyboardState = SDL_GetKeyboardState(NULL);
                if (keyboardState[SDL_SCANCODE_SPACE])
                {
                    // Space key is pressed
                }
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                // Handle mouse click event
                int mouseX, mouseY;
                Uint32 mouseState = SDL_GetMouseState(&mouseX, &mouseY);
                if (mouseState & SDL_BUTTON(SDL_BUTTON_LEFT))
                {
                    // Left mouse button is pressed
                }
            }
        }

        gameState.update(deltaTime);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        gameState.render(renderer);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void GameState::render(SDL_Renderer* renderer) {
    // Render game graphics using SDL2 rendering functions
    renderGalaxy(renderer);
    renderPlanets(renderer);
    renderShips(renderer);
    renderPlayers(renderer);
    renderUI(renderer);
}

void GameState::renderGalaxy(SDL_Renderer* renderer) {
    // Render the galaxy background using SDL2 rendering functions
    SDL_Texture* texture = IMG_LoadTexture(renderer, "galaxy_background.png");
    SDL_Rect destRect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
    SDL_RenderCopy(renderer, texture, NULL, &destRect);
    SDL_DestroyTexture(texture);
}

void GameState::renderPlanets(SDL_Renderer* renderer) {
    for (Planet* planet : planets) {
        planet->render(renderer);
    }
}

void GameState::renderShips(SDL_Renderer* renderer) {
    for (Ship* ship : ships) {
        ship->render(renderer);
    }
}

void GameState::renderPlayers(SDL_Renderer* renderer) {
    for (Player* player : players) {
        player->render(renderer);
    }
}

void GameState::renderUI(SDL_Renderer* renderer) {
    // Render the game UI using SDL2 rendering functions
    TTF_Font* font = TTF_OpenFont("font.ttf", 24);
    SDL_Color color = { 255, 255, 255, 255 };
    SDL_Surface* surface = TTF_RenderText_Solid(font, "Hello, SDL!", color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect destRect = { 10, 10, surface->w, surface->h };
    SDL_RenderCopy(renderer, texture, NULL, &destRect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    TTF_CloseFont(font);
}
