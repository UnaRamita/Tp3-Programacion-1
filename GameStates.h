#pragma once

enum class GameState {
    PLAYING,         // El tren se mueve por las vías
    WAITING_RTA,   // El tren se detuvo por una colision y espera la suma
    GAMEOVER,        // Perdio la locomotora y los vagones iniciales
    VICTORI         // Llegp al final del recorrido
};
