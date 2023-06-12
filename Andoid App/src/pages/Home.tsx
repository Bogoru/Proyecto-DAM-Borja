import { IonContent, IonPage } from '@ionic/react';
import './Home.css';
import Logo from '../imagenes/Logo.png';

function Home () {

  function cambiarVentana(){
    window.location.href = '/Dispositivos';  
  }

  setTimeout(cambiarVentana, 2000);

  return (
    <IonPage>
      <IonContent fullscreen className='fondo'>
        <div className='contenedor'>        
          <img src={Logo} className='Logo'></img>
        </div>
      </IonContent>
    </IonPage>
  );
};

export default Home;

