import java.util.Random;

public class Main {
    public static void main(String[] args) {
        CustomHashSet<Integer> set = new CustomHashSet<>(10);

        Random rand = new Random();

        for(int i = 0; i < 4; i++){
            set.insert(3123123 + i*1234);
        }

        System.out.println(set.capacity());
        set.print();

        set.erase(3124357);
        set.print();
    }
}