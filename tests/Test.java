public class Test {
	public Test() {
	}

	public static void main(String[] args) {
		System.out.println("Hello, World");

		Test t = new Test();
		t.test();
	}

	public void test() {
		long y = testfunc(0xcafebabe);
		System.out.println(y);
	}

	public long testfunc(long max) {
		long y = -1;
		for (long i = 0; i < max; i++) {
			for (long k = 2; k < i; ++k) {
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
