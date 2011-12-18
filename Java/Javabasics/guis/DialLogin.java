package guis;

import java.awt.*;
import java.awt.event.*;

import utils.StringChecker;

public class DialLogin extends Dialog implements ActionListener
{
	private TextField fieldNomPrenom;
	private TextField fieldPort;
	private Button buttonOk;
	private Button buttonAnnuler;

	public DialLogin()
	{
		super((Frame) null, "Connexion");

		this.setLayout(new GridLayout(3, 2));

		this.fieldNomPrenom = new TextField();
		this.fieldPort = new TextField();
		this.buttonOk = new Button("Ok");
		this.buttonAnnuler = new Button("Annuler");

		this.add(new Label("Nom et prénom: "));
		this.add(this.fieldNomPrenom);
		this.add(new Label("Port de communication: "));
		this.add(this.fieldPort);
		this.add(this.buttonOk);
		this.add(this.buttonAnnuler);

		this.buttonOk.addActionListener(this);
		this.buttonAnnuler.addActionListener(this);

		this.addWindowListener(new WindowAdapter() {
			public void windowClosing(WindowEvent e)
            {
                DialLogin.this.setVisible(false);
                System.exit(0);
            }
		});
		
		this.pack();
	}

	public void actionPerformed(ActionEvent e)
	{
		if (e.getActionCommand() == "Ok") {
			if (!StringChecker.isUnsignedShort(this.getPort()))
				this.setTitle("Port non valide (entier positif inférieur à 65536");
			else {
				this.setTitle(String.format(
					"Connecté en tant que %s (%s)",
					this.getNomPrenom(), this.getPort()
				));
			}
		} else if (e.getActionCommand() == "Annuler") {
			this.setVisible(false);
			System.exit(0);	
		}
	}

	public String getNomPrenom()
	{
		return this.fieldNomPrenom.getText();
	}
	
	public String getPort()
	{
		return this.fieldPort.getText();
	}
}
