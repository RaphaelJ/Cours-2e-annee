package utils;

public class StringChecker
{
	public static boolean isUnsignedShort(String str)
	{
		int i;
		try {
			i = Integer.parseInt(str);
		} catch (NumberFormatException e) {
			return false;
		}

		return i > 0 && i < 65536;
	}
}
