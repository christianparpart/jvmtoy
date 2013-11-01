public class Test {
	public Test() {
	}

	public static void main(String[] args) {
		System.out.println("Hello, World");

		Test t = new Test();
		t.test();
	}

	public void test() {
		int y = testfunc(42);
		System.out.println(y);
	}

	public int testfunc(int max) {
		int y = -1;
		for (int i = 0; i < max; i++) {
			for (int k = 2; k < i; ++k) {
				if ((i % k) == 0) {
					y += i;
					break;
				}
			}
			System.out.println(i);
		}
		return y;
	}

	public native void fnord();
	public native void fnord(int i);
	public native void fnord(int i, String s);
	public native String fnord2();
	public native String fnord2(int i);

	static {
		System.loadLibrary("fnord");
	}
};
