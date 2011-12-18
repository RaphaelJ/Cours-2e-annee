package utils;

public class ValidPortCheckerTest
{
	public static void main(String[] args)
	{
		if (StringChecker.isUnsignedShort("58")
		    && !StringChecker.isUnsignedShort("0")
			&& !StringChecker.isUnsignedShort("65536"))
			System.out.println("ok");
		else
			System.out.println("no ok");
	}
}
