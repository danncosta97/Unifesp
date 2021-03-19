package Decorator;

public class Main {
	public static void main(String[] args){
        ComponenteConcreto string = new ComponenteConcreto("String teste");
        DecoratorUpper upper = new DecoratorUpper(string);
        DecoratorReverse reverse = new DecoratorReverse(string);
        DecoratorTag tag = new DecoratorTag(string);
        
        upper.op();
        System.out.println(string.getString());
       
        reverse.op();
        System.out.println(string.getString());
        
        tag.op();
        System.out.println(string.getString());
    }
}
