import java.awt.*;
import javax.swing.*;

public class Puzzle extends JApplet
{
    public void init()
    {
        PuzzleGrid pgGrid = new PuzzleGrid();

        add(pgGrid.bNewGame, BorderLayout.NORTH);
        add(pgGrid, BorderLayout.CENTER);
        add(pgGrid.lMoves, BorderLayout.SOUTH);
    }
}