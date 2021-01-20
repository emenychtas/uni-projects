import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.border.*;
import java.util.*;

public class PuzzleGrid extends JPanel implements ActionListener, MouseListener
{
    PuzzleTile[][] ptTiles = new PuzzleTile[3][3];
    PuzzleTile ptZeroTile = null;
    int moves;
    
    public JButton bNewGame = new JButton("New Game");
    public JLabel lMoves = new JLabel("Moves: 0", JLabel.CENTER);
    
    public PuzzleGrid()
    {
        bNewGame.setFocusPainted(false);
        bNewGame.addActionListener(this);
        bNewGame.setActionCommand("new");
        
        setLayout(new GridLayout(3,3,8,8));
        setBorder(new EmptyBorder(8,8,8,8));
        setBackground(Color.BLACK);
        
        newGame();
    }
    
    private void newGame()
    {
        lMoves.setText("Moves: 0");
        moves = 0;
        
        removeAll();
        
        Random randomGen = new Random();
        int Drawn[] = new int[9];
        int Draw = -1;
        boolean Found;
        
        for(int i=0; i<9; i++) Drawn[i] = -1;
        
        for(int i=0; i<9; i++) {
            Found = false;
            while(!Found) {
                Found = true;
                Draw = randomGen.nextInt(9);
                for(int j=0; j<i; j++) if(Drawn[j] == Draw) Found = false;
            }
            Drawn[i] = Draw;
        }
        
        for(int i=0; i<3; i++) {
            for(int j=0; j<3; j++) {
                int Number = Drawn[(i*3)+j];
                
                ptTiles[i][j] = new PuzzleTile(i,j,Number);
                ptTiles[i][j].addMouseListener(this);
                
                add(ptTiles[i][j]);
                if(Number == 0) ptZeroTile = ptTiles[i][j];
            }
        }
        
        revalidate();
    }
    
    private boolean isSolved()
    {
        for(int i=0; i<3; i++) {
            for(int j=0; j<3; j++) {
                if((ptTiles[i][j].Number != (i*3)+(j+1)) && (ptTiles[i][j].Number != 0)) return false;
            }
        }
        return true;
    }
    
    private void moveTile(PuzzleTile ptMovingTile)
    {
        ptZeroTile.setBackground(Color.GRAY);
        ptZeroTile.Number = ptMovingTile.Number;
        ptZeroTile.lText.setText(Integer.toString(ptZeroTile.Number));
        
        ptZeroTile = ptMovingTile;
        
        ptZeroTile.Number = 0;
        ptZeroTile.lText.setText("");
        ptZeroTile.setBackground(Color.BLACK);
    }
    
    public void actionPerformed(ActionEvent e)
    {
        String command = e.getActionCommand();
        
        if(command == "new") newGame();
    }
    
    public void mousePressed(MouseEvent e)
    {
        PuzzleTile ptClickedTile = (PuzzleTile)e.getSource();
        
        if(ptClickedTile.isNextTo(ptZeroTile))
        {
            moveTile(ptClickedTile);
            
            moves++;
            lMoves.setText("Moves: " + Integer.toString(moves));
            
            if(isSolved())
            {
                JOptionPane.showMessageDialog(null, "Well Done!!!", "You Won!", JOptionPane.INFORMATION_MESSAGE);
                newGame();
            }
        }
    }
    public void mouseReleased(MouseEvent e) {}
    public void mouseClicked(MouseEvent e) {}
    public void mouseEntered(MouseEvent e) {}
    public void mouseExited(MouseEvent e) {}
}

class PuzzleTile extends JPanel
{
    public int X, Y, Number;
    public JLabel lText = new JLabel();

    public PuzzleTile(int x, int y, int Num)
    {
        X = x;
        Y = y;
        Number = Num;
        
        lText.setForeground(Color.WHITE);
        lText.setHorizontalAlignment(JLabel.CENTER);
        lText.setFont(new Font(Font.SANS_SERIF,Font.BOLD,32));
        
        if(Num == 0)
        {
            setBackground(Color.BLACK);
            lText.setText("");
        }
        else
        {
            setBackground(Color.GRAY);
            lText.setText(Integer.toString(Num));
        }
        
        setLayout(new GridLayout());
        add(lText);
    }
    
    public boolean isNextTo(PuzzleTile ptOther)
    {
        int dX = Math.abs(X - ptOther.X);
        int dY = Math.abs(Y - ptOther.Y);
        
        if((dX+dY) == 1) return true;
        else return false;
    }
}