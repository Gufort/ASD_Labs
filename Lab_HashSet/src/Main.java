import java.util.Random;

public class Main {
    public static void main(String[] args) {
        CustomHashSet<Integer> set = new CustomHashSet<>(10);

        Random r = new Random();

        for (int i = 1; i <= 4; i++)
            set.insert(i*123123);

        set.print();

        System.out.println(set.find(246246));
        set.erase(492492);
        set.print();
    }
}