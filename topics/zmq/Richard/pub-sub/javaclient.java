import org.zeromq.ZMQ;

// javac -cp jeromq-0.3.4.jar  javaclient.java
// java -cp jeromq-0.3.4.jar:. javaclient

public class javaclient {

    public static void main( String[] args ) {
        ZMQ.Context context = ZMQ.context( 1 );

        //  Socket to talk to server
        System.out.println( "Connecting to localhost:5555" );
        ZMQ.Socket subscriber = context.socket( ZMQ.SUB );
        subscriber.connect( "tcp://localhost:5555" );

        subscriber.subscribe( "200".getBytes() );
        subscriber.subscribe( "210".getBytes() );
        subscriber.subscribe( "235".getBytes() );

        while ( true ) {
            String string = subscriber.recvStr( 0 ).trim();
            System.out.println( "Received: " + string );
        }

        //subscriber.close();
        //context.term();
    }
}
