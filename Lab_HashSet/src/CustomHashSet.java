import java.util.*;
import java.util.function.*;

public class CustomHashSet<T> {
    private char[] _states; // 0 - пусто, 1 - занято, 2 - удалено
    private int _size;
    private int _capacity;
    private int _countOfCollisions;
    private Comparator<T> _compare;
    private Function<T, Integer> _hashFuction;
    private Object[] _elements;

    public CustomHashSet(int capacity, Function<T, Integer> hashFuction, Comparator<T> compare) {
        _capacity = capacity;
        _hashFuction = hashFuction;
        _compare = compare;
        _size = 0;
        _countOfCollisions = 0;
        _elements = new Object[_capacity];

        //Все клетки пустые
        _states = new char[_capacity];
        for(int i = 0; i < capacity; i++)
            _states[i] = '0';
    }

    public CustomHashSet(int capacity) {
        this(capacity,
                key -> (key == null) ? 0 : key.hashCode(),
                (a, b) -> a.equals(b) ? 0 : 1);
    }

    private int hash(T element) {
        return Math.abs(_hashFuction.apply(element)) % _capacity;
    }

    public int size() { return _size; }
    public int capacity() { return _capacity; }
    public int countOfCollisions() { return _countOfCollisions; }

    public boolean insert(T element) {
        if (_size >= _capacity)
            throw new IllegalStateException("Hash table is full");

        int position = hash(element);
        int start = position;

        while(true) {
            if(_states[position] != '1') {
                _elements[position] = element;
                _states[position] = '1';
                _size++;
                return true;
            }

            else if(_states[position] == '1' &&
                    _compare.compare((T)_elements[position], element) == 0) {
                return false;
            }

            _countOfCollisions++;
            position = (position + 1) % _capacity;
        }
    }

    public boolean erase(T element) {
        int position = hash(element);
        int start = position;

        while(true) {
            if(_states[position] == '0')
                return false;

            if(_states[position] == '1' &&
                    _compare.compare((T)_elements[position], element) == 0) {
                _elements[position] = null;
                _states[position] = '2';
                _size--;
                return true;
            }

            position = (position + 1) % _capacity;
        }
    }

    public boolean find(T element) {
        int position = hash(element);
        int start = position;

        while(true) {
            if(_states[position] == '0')
                return false;

            else if(_states[position] == '1' && _compare.compare((T)_elements[position], element) == 0)
                return true;
            position = (position + 1) % _capacity;
        }
    }

    public void print(){
        System.out.println("Hash table:");
        System.out.printf("%-10s %-15s %-15s %s%n", "Value", "Hash", "Key", "State");

        for(int i = 0; i < _capacity; i++){
            String s = (_states[i] == '1') ? "Занято" :
                    (_states[i] == '0') ? "Свободно" :
                            "Удалено";

            System.out.printf("%-10d %-15s %-15s %s%n",
                    i,
                    (_states[i] == '0') ? "empty" : hash((T)_elements[i]),
                    (_states[i] == '0' || _states[i] == '2') ? "empty" :
                            (_elements[i] != null) ? _elements[i].toString() : "null",
                    s);
        }
    }
}
