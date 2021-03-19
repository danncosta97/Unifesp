package banco;

public class Cliente {
	public static void main(String args[]) {
		Server server = new Server();
		
		server.service("new", "Ronaldo");
		server.service("new", "Neymar");
		server.service("new", "Jesus");
		server.service("new", "William");
		
		server.service("del", 0);
		server.service("get", 2);
		server.service("all", 0);
	}
}
