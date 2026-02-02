#ifndef GAMESETTINGS_H
#define GAMESETTINGS_H

/** * @class GameSettings
 * @brief Singleton Pattern: Garanteaza existenta unei singure configuratii globale in joc.
 */
class GameSettings {
private:
    static GameSettings* instance;
    int difficultyLevel;

    /** @brief Constructor privat pentru a impiedica instantierea din exterior. */
    GameSettings() : difficultyLevel(1) {}

public:
    /** @brief Metoda statica pentru accesarea instantei unice. */
    static GameSettings& getInstance() {
        if (!instance) {
            instance = new GameSettings();
        }
        return *instance;
    }

    /** @brief Dezactivam constructorul de copiere pentru a pastra unicitatea. */
    GameSettings(const GameSettings&) = delete;
    /** @brief Dezactivam operatorul de atribuire. */
    void operator=(const GameSettings&) = delete;

    int getDifficulty() const { return difficultyLevel; }
    void setDifficulty(int d) { difficultyLevel = d; }
};

#endif