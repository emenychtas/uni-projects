import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class ImageApplication extends JFrame implements ActionListener
{
    Image myImage;
    JLabel myImageLabel;
    ImageIcon myImageIcon;
    
    int origWidth, origHeight;
    JTextField txtWidth, txtHeight;
    
    public static void main(String[] args)
    {
        ImageApplication ia = new ImageApplication("Image Application");
        ia.setVisible(true);
    }
    
    public ImageApplication(String title)
    {
        super(title);
        
        myImageIcon = new ImageIcon("rodeo.jpg");
        myImageLabel = new JLabel(myImageIcon, JLabel.CENTER);
        myImage = myImageIcon.getImage();
        
        origWidth = myImageIcon.getIconWidth();
        origHeight = myImageIcon.getIconHeight();
        
        JMenuBar myMenuBar = new JMenuBar();
        JMenu myMenu = new JMenu("Options");
        JMenuItem myMenuItem1 = new JMenuItem("Double");
        JMenuItem myMenuItem2 = new JMenuItem("Reset");
        myMenu.add(myMenuItem1);
        myMenu.add(myMenuItem2);
        myMenuBar.add(myMenu);
        setJMenuBar(myMenuBar);
        
        JButton bAL = new JButton("Align Left");
        JButton bAC = new JButton("Align Center");
        JButton bAR = new JButton("Align Right");
        JButton bResize = new JButton ("Resize");
        bAL.setFocusPainted(false);
        bAC.setFocusPainted(false);
        bAR.setFocusPainted(false);
        bResize.setFocusPainted(false);
        
        JLabel lWidth = new JLabel("Width:");
        JLabel lHeight = new JLabel("Height:");
        txtWidth = new JTextField(Integer.toString(origWidth));
        txtHeight = new JTextField(Integer.toString(origHeight));
        
        JPanel GRID = new JPanel(new GridBagLayout());
        GridBagConstraints c = new GridBagConstraints();
        
        c.fill = GridBagConstraints.BOTH;
        c.weightx = 1f;
        c.weighty = 0f;
        
        c.gridx = 0;
        c.gridy = 0;
        GRID.add(bAL, c);
        c.gridx++;
        GRID.add(bAC, c);
        c.gridx++;
        GRID.add(bAR, c);
        
        c.gridx = 0;
        c.gridy = 1;
        c.gridwidth = 3;
        GRID.add(myImageLabel, c);
        c.gridwidth = 1;
        
        c.gridx = 0;
        c.gridy = 2;
        GRID.add(lWidth, c);
        c.gridx++;
        c.gridwidth = 2;
        GRID.add(txtWidth, c);
        c.gridwidth = 1;
        
        c.gridx = 0;
        c.gridy = 3;
        GRID.add(lHeight, c);
        c.gridx++;
        c.gridwidth = 2;
        GRID.add(txtHeight, c);
        c.gridwidth = 1;
        
        c.gridx = 0;
        c.gridy = 4;
        GRID.add(bResize, c);
        
        add(GRID, BorderLayout.CENTER);
        setSize(origWidth + 150, origHeight + 150);
        
        myMenuItem1.addActionListener(this);
        myMenuItem1.setActionCommand("double");
        myMenuItem2.addActionListener(this);
        myMenuItem2.setActionCommand("reset");
        bAL.addActionListener(this);
        bAL.setActionCommand("left");
        bAC.addActionListener(this);
        bAC.setActionCommand("center");
        bAR.addActionListener(this);
        bAR.setActionCommand("right");
        bResize.addActionListener(this);
        bResize.setActionCommand("resize");
    }
    
    private void ResizeImage(int Width, int Height)
    {
        myImage = myImage.getScaledInstance(Width, Height, Image.SCALE_SMOOTH);
        myImageIcon.setImage(myImage);
        myImageLabel.setIcon(myImageIcon);
        
        txtWidth.setText(Integer.toString(Width));
        txtHeight.setText(Integer.toString(Height));
        
        setSize(Width + 150, Height + 150);
    }
    
    public void actionPerformed(ActionEvent e)
    {
        String command = e.getActionCommand();
        
        if(command == "left") myImageLabel.setHorizontalAlignment(JLabel.LEFT);
        else if(command == "center") myImageLabel.setHorizontalAlignment(JLabel.CENTER);
        else if(command == "right") myImageLabel.setHorizontalAlignment(JLabel.RIGHT);
        else if(command == "resize") ResizeImage(Integer.parseInt(txtWidth.getText()), Integer.parseInt(txtHeight.getText()));
        else if(command == "double") ResizeImage(myImageIcon.getIconWidth() * 2, myImageIcon.getIconHeight() * 2);
        else if(command == "reset") ResizeImage(origWidth, origHeight);
    }
}