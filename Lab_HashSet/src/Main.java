import java.util.*;

public class Main {

    public static void testingCustomHashSet(){
        int capacity = 2000;
        int size = 1000;

        Random random = new Random();
        List<Integer> lst = new ArrayList<Integer>();

        for (int i = 0; i < size; i++) {
            lst.add(random.nextInt(10000));
        }

        CustomHashSet<Integer> customHashSet = new CustomHashSet<Integer>(capacity);
        long startTime = System.nanoTime();

        for(int curr: lst)
            customHashSet.insert(curr);

        long endTime = System.nanoTime();
        long elapsedTimeForCustom = endTime - startTime;

        Set<Integer> treeSet = new TreeSet<Integer>();
        startTime = System.nanoTime();

        for(int curr: lst)
            treeSet.add(curr);

        endTime = System.nanoTime();
        long elapsedTimeForTree = endTime - startTime;

        System.out.println("Вставка 1000 элементов в CustomHashSet заняла: " + elapsedTimeForCustom);
        System.out.println("Вставка 1000 элементов в TreeSet заняла: " + elapsedTimeForTree);

        List<Integer> lstForOperations = new ArrayList<Integer>();
        for(int i = 0; i < 100; i++)
            lstForOperations.add(random.nextInt(10000));

        treeSet.clear();
        customHashSet.clear();

        startTime = System.nanoTime();
        for(int curr: lstForOperations)
            customHashSet.insert(curr);
        for(int i = 0; i < 50; i++)
            customHashSet.find(lstForOperations.get(i));
        for(int curr: lstForOperations)
            customHashSet.erase(curr);
        endTime = System.nanoTime();
        long elapsedTimeForOperationByCustom = endTime - startTime;

        startTime = System.nanoTime();
        for(int curr: lstForOperations)
            treeSet.add(curr);
        for(int i = 0; i < 50; i++)
            treeSet.contains(lstForOperations.get(i));
        for(int curr: lstForOperations)
            treeSet.remove(curr);
        endTime = System.nanoTime();
        long elapsedTimeForOperationByTreeSet = endTime - startTime;

        System.out.println("На все операции у CustomHashSet ушло: " + elapsedTimeForOperationByCustom);
        System.out.println("На все операции у TreeSet ушло: " + elapsedTimeForOperationByTreeSet);

        customHashSet.printInfo();
    }

    public static void main(String[] args) {
        testingCustomHashSet();
    }
}