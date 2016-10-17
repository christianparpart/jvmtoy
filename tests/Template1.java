public class Template1<T> {
	private T first;
	private T second;

	public Template1(T a, T b) {
		first = a;
		second = b;
	}

	public String toString() {
		return this.first  + ", " + this.second;
	}

	public T sum() {
		return first + second;
	}

	public static void main(String[] args) {
		Template1<String> s = new Template1<String>("foo", "bar");
		Template1<Integer> i = new Template1<Integer>(4, 2);

		System.out.println("s: " + s);
		System.out.println("i: " + i);
	}
}
