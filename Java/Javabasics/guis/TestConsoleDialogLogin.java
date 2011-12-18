package guis;

public class TestConsoleDialogLogin
{
	public static void main(String[] args)
	{
		DialLogin d = new DialLogin();
		d.setVisible(true);

		System.out.println(String.format(
			"User: %s\nPort: %s",
			d.getNomPrenom(), d.getPort()
		));
	}
}
