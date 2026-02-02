#ifndef GAMESETTINGS_H
#define GAMESETTINGS_H

/** * @class GameSettings
 * @brief DESIGN PATTERN: Singleton. Gestioneaza setarile globale ale jocului.
 */
class GameSettings {
private:
    int difficultyLevel;
    static GameSettings* instance;

    // Constructor privat pentru Singleton
    GameSettings() : difficultyLevel(1) {}

public:
    // Stergem constructorul de copiere si operatorul=
    GameSettings(const GameSettings&) = delete;
    GameSettings& operator=(const GameSettings&) = delete;

    static GameSettings& getInstance() {
        if (!instance) {
            instance = new GameSettings();
        }
        return *instance;
    }

    int getDifficulty() const { return difficultyLevel; }

    /** @brief Marcarea ca [[maybe_unused]] repara eroarea de pe GitHub */
    [[maybe_unused]] void setDifficulty(int d) {
        difficultyLevel = d;
    }
};

#endif