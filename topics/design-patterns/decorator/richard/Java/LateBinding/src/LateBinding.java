// LateBinding.java
public class LateBinding {
    public static void main(String[] args) {
        Foo f = new Foo();
        Bar b = new Bar();
        FooBar fb;
        for (int i = 1; i <= 10; ++i) {
            int r = 1 + (int) (Math.random() * 10);
            if (r > 5) {
                fb = f;
            } else {
                fb = b;
            }
            fb.doSomething();
        }
    }
}
