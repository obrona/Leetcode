# min time is simply the number of booked seats.
# since there is toggle we need to store the history.

class BusBooking:

    def __init__(self, n: int):
        self.store = dict[str, int]()
        self.total = 0

    def toggle(self, seat: str) -> None:
        if seat in self.store:
            self.total -= self.store.pop(seat)
        else:
            type = seat[0]
            row = seat[1:]
            if type == 'B' or type == 'C':
                self.store[seat] = 1
                self.total += 1
            else:
                to_check = ('B' if type == 'A' else 'C') + row
                cost = 3 if to_check in self.store else 1
                self.store[seat] = cost
                self.total += cost

    def getTotalTime(self) -> int:
        return self.total

    def getMinTime(self) -> int:
        return len(self.store)

sol = BusBooking(20)
sol.toggle('B3')
sol.toggle('A3')
print(sol.getTotalTime())
print(sol.getMinTime())
        
