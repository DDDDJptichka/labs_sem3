#pragma once

enum class Cell{Empty, X, O};

Cell operator!(Cell cell){

    if (cell == Cell::X){

        return Cell::O;

    }

    if (cell == Cell::O){

        return Cell::X;

    }

    return Cell::Empty;

};