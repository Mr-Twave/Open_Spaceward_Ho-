#include <iostream>
#include <vector>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT = 768;

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

    Planet(int x, int y, int playerOwner, int population, double temperature, double gravity, double metal)
        : x(x), y(y), playerOwner(playerOwner), population(population), temperature(temperature),
          gravity(gravity), metal(metal), terraformingLevel(0), miningLevel(0), shipbuildingCapacity(0), defenseLevel(0) {
        incomeGenerated = new double[5]{0.0, 0.0, 0.0, 0.0, 0.0};
        devotedResources = new double[5]{0.0, 0.0, 0.0, 0.0, 0.0};
        orbitalShips = new std::vector<int>();
        shipsInProduction = new std::vector<int>();
    }

    ~Planet() {
        delete[] incomeGenerated;
        delete[] devotedResources;
        delete orbitalShips;
        delete shipsInProduction;
    }

    void update(double deltaTime);
    void render(SDL_Renderer* renderer);

    // ... (other planet-related functions)
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

    void update(double deltaTime);
    void render(SDL_Renderer* renderer);
};

struct Technology {
    std::string name;
    int currentLevel;
    double costToUpgrade;
    std::vector<double>* effects;

    Technology(const std::string& name, int currentLevel, double costToUpgrade) 
        : name(name), currentLevel(currentLevel), costToUpgrade(costToUpgrade) {
        effects = new std::vector<double>();        
    }

    ~Technology() {
        delete effects;
    }

    void update(double deltaTime);
    void render(SDL_Renderer* renderer);
};
struct Player
{
    int playerNumber;
    std::string playerName;
    double temperaturePreference;
    double gravityPreference;
    int totalPopulation;
    double totalFundsAccumulated;
    double totalFundsInBank;
    double totalGrossIncomePerTurn;
    double totalFundsSpentOnTechnology;
    std::vector<int> *technologyLevels;
    std::vector<int> *planetsOwned;
    std::vector<int> *planetsSeen;
    std::vector<int> *propertiesSeenInPossessionOfOtherPlayer;
    int numberOfShipsOwned;
    int researchPoints;
    std::vector<int> *diplomacyStatus;

    Player(int playerNumber, const std::string &playerName, double temperaturePreference, double gravityPreference)
        : playerNumber(playerNumber), playerName(playerName), temperaturePreference(temperaturePreference),
          gravityPreference(gravityPreference), totalPopulation(0), totalFundsAccumulated(0.0),
          totalFundsInBank(0.0), totalGrossIncomePerTurn(0.0), totalFundsSpentOnTechnology(0.0),
          numberOfShipsOwned(0), researchPoints(0)
    {
        technologyLevels = new std::vector<int>();
        planetsOwned = new std::vector<int>();
        planetsSeen = new std::vector<int>();
        propertiesSeenInPossessionOfOtherPlayer = new std::vector<int>();
        diplomacyStatus = new std::vector<int>();
    }

    ~Player()
    {
        delete technologyLevels;
        delete planetsOwned;
        delete planetsSeen;
        delete propertiesSeenInPossessionOfOtherPlayer;
        delete diplomacyStatus;
    }
    void updateTotalPopulation();
    void updateTotalFunds();
    void updateGrossIncome();
    void investInTechnology(int technologyIndex, double funds);
    void addPlanetOwned(int planetId);
    void addPlanetSeen(int planetId);
    void addPropertySeenInPossessionOfOtherPlayer(int propertyId);
    void updateDiplomacyStatus(int playerNumber, int status);
    void buildShip(int planetId, int shipType);
};

struct GUIElement {
    int upperLeftX, upperLeftY;
    int bottomRightX, bottomRightY;
};

class Galaxy
{
public:
    Galaxy();
    void update(double deltaTime);
    void render(SDL_Renderer *renderer);

private:
    std::vector<Planet> planets;
    std::vector<int> turnsTaken;
    std::vector<double> initialValues;
    std::vector<double *> populationGrowthCalculations;
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
    std::vector<double *> technologyEffectEquations;
    std::vector<int> battleData;
    std::vector<Ship> ships;
    std::vector<Technology> technologies;
};

class GameUI
{
public:
    GameUI(Galaxy &galaxy);
    void render(SDL_Renderer *renderer);
    void displayPlanetInfo(int planetId);
    void showShipOrbits(int planetId);
    void updateTechTreeUI();
    void updateMinimap();
    void renderGalaxyView();
    void displayShipInfo(int shipId);
    void displayTechnologyInfo(int techIndex);
    void displayPlayerInfo(int playerNumber);

private:
    Galaxy &gameGalaxy;
};

class GameLogic
{
public:
    GameLogic(Galaxy &galaxy);
    void update(double deltaTime);
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
    void colonizePlanet(Player &player, Planet &planet);
    void developPlanet(Player &player, Planet &planet);
    void conductEspionage(Player &player, Player &targetPlayer);
    void conductSabotage(Player &player, Player &targetPlayer);

private:
    Galaxy &gameGalaxy;
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

class SaveGame {
public:
    SaveGame(const Galaxy& galaxy);
    void saveGameState(const std::string& filename);
    void loadGameState(const std::string& filename);

private:
    const Galaxy& gameGalaxy;
};

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

void Player::render() {
    // Render the player's UI and other visual elements
}

void Player::loseResources(double amount) {
    // Deduct resources from the player
    // ...
}

