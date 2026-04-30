#pragma once

enum class GameState {
    JUGANDO,         // El tren se mueve por las vías
    ESPERANDO_RTA,   // El tren se detuvo por una colisión y espera la suma
    GAMEOVER,        // Perdió la locomotora y los vagones iniciales
    VICTORIA         // Llegó al final del recorrido
};
