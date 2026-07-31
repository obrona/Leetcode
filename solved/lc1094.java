// just a simple sweep line algorithm.

import java.util.ArrayList;
import java.util.Collections;

abstract class Event implements Comparable<Event> {
    int time;
    int numOfPassengers;

    @Override
    public int compareTo(Event other) {
        return Integer.compare(time, other.time);
    }
    
}

class StartEvent extends Event {
    StartEvent(int time, int numOfPassengers) {
        this.time = time;
        this.numOfPassengers = numOfPassengers;
    }
}

class EndEvent extends Event {
    EndEvent(int time, int numOfPassengers) {
        this.time = time;
        this.numOfPassengers = numOfPassengers;
    }
}

class Solution {
    public boolean carPooling(int[][] trips, int capacity) {
        ArrayList<Event> arr = new ArrayList<>();
        for (int[] t : trips) {
            arr.add(new StartEvent(t[1], t[0]));
            arr.add(new EndEvent(t[2], t[0]));
        }

        Collections.sort(arr);

        int p = 0;
        int cap = 0;
        while (p < arr.size()) {
            int time = arr.get(p).time;
            while (p < arr.size() && arr.get(p).time == time) {
                Event e = arr.get(p);
                if (e instanceof StartEvent) cap += e.numOfPassengers;
                else if (e instanceof EndEvent) cap -= e.numOfPassengers;
                p++;
            }
            if (cap > capacity) return false;
        }
        return true;
    }
}