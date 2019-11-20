world_X = 10000;
world_Y = 10000;
A_loss_per_cycle = 0.0045;
B_loss_per_cycle = 0.0045;
A_initial = 10;
B_initial = 10;
MaxSensorDistance = 1500;
A_Max = 40;
B_Max = 40;
A_A = 1;
B_B = 1;
A_B = -0.2;
B_A = -0.2;
number_of_A = 50;
number_of_B = 50;
distance_per_cycle = 10;
A_radius = 60;
B_radius = 60;
agent_radius = 60;

class Agent :
    def scan(self) :
        self.A = 0;
        self.B = 0;
        self.alive = True;
        return ;
    def update(self):
        if (A<0 or B<0):
            self.alive = False
    def consume(self,ressource):
        if (ressource.type == 'A'):
            self.update_A()

class Map:
