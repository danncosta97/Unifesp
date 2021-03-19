package banco;

import java.util.HashMap;

public class Server {
	public static HashMap bd = new HashMap();
	public static HashMap cmds = new HashMap();
	
	public Server() {
		initCommands();
	}
	
	public void initCommands() {
		cmds.put("new", new newCommand(bd));
		cmds.put("del",new delCommand(bd));
		cmds.put("get",new getCommand(bd));
		cmds.put("all",new AllCommand(bd));
	}
	
	public void service(String cmd,Object data) {
		Command c = (Command) cmds.get(cmd);
		this.bd = (HashMap) c.execute(data);
	}
	
	
}
