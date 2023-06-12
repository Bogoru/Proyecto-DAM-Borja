import { IonContent, IonHeader, IonCheckbox, IonPage, IonToolbar } from '@ionic/react';
import './Lluvia.css';
import { ReactSVG } from 'react-svg';
import { BleClient, numbersToDataView } from '@capacitor-community/bluetooth-le';
import { BLE } from '@ionic-native/ble';
import { useEffect, useState } from 'react';


import Lluvia from '../imagenes/titulolluvia.svg';
import Volver from '../imagenes/volver.svg'

function Home () {

  const HEART_RATE_SERVICE = '0000abcd-0000-1000-8000-00805f9b34fb';
  const READ_CHARACTERISTIC = "00001111-0000-1000-8000-00805F9B34FB";
  const WRITE_CHARACTERISTIC = "00001111-0000-1000-8000-00805F9B34FB";

  const [isChecked, setIsChecked] = useState(false);

  useEffect(() => {
    const interval = setInterval(() => {

      BLE.connectedPeripheralsWithServices([HEART_RATE_SERVICE]).then(
        async peripherals => {
          console.log('Dispositivos conectados con el servicio ' + HEART_RATE_SERVICE + ':');
          for(let i = 0; i < peripherals.length; i++) {
            console.log(peripherals[i].id);
          }

          if(peripherals.length <= 0){
            window.location.href ='/Dispositivos';
          }

        },
        error => {
          console.log('Error al buscar dispositivos conectados: ' + error);
        }
      );

    }, 1000);

    setTimeout(comprobar, 20);

    function comprobar(){
      BLE.connectedPeripheralsWithServices([HEART_RATE_SERVICE]).then(
        async peripherals => {
          console.log('Dispositivos conectados con el servicio ' + HEART_RATE_SERVICE + ':');
          for(let i = 0; i < peripherals.length; i++) {
            console.log(peripherals[i].id);
            const estado = await BleClient.read(peripherals[i].id, HEART_RATE_SERVICE, READ_CHARACTERISTIC);
            if(estado.getUint8(0) == 0){
              setIsChecked(false)
            }else if(estado.getUint8(0) == 1){
              setIsChecked(true)
            }
          }
        },
        error => {
          console.log('Error al buscar dispositivos conectados: ' + error);
        }
      );
    }

  }, []);

  const guardar = (event) => {
    
    setIsChecked(event.target.value);

    if(isChecked == false){
      setIsChecked(true);

      BLE.connectedPeripheralsWithServices([HEART_RATE_SERVICE]).then(
        async peripherals => {
          console.log('Dispositivos conectados con el servicio ' + HEART_RATE_SERVICE + ':');
          for(let i = 0; i < peripherals.length; i++) {
            console.log(peripherals[i].id);
            await BleClient.write(peripherals[i].id, HEART_RATE_SERVICE, WRITE_CHARACTERISTIC, numbersToDataView([1]));
          }
        },
        error => {
          console.log('Error al buscar dispositivos conectados: ' + error);
        }
      );

    }else if(isChecked == true){
      setIsChecked(false);
      console.log("Seteado false");

      BLE.connectedPeripheralsWithServices([HEART_RATE_SERVICE]).then(
        async peripherals => {
          console.log('Dispositivos conectados con el servicio ' + HEART_RATE_SERVICE + ':');
          for(let i = 0; i < peripherals.length; i++) {
            console.log(peripherals[i].id);
            await BleClient.write(peripherals[i].id, HEART_RATE_SERVICE, WRITE_CHARACTERISTIC, numbersToDataView([0]));
          }
        },
        error => {
          console.log('Error al buscar dispositivos conectados: ' + error);
        }
      );
      
    }

  }

    function back(){
      window.location.href ='/Menu';
    }
    
  return (
    <IonPage>

        <IonHeader className='fondoLluvia'>
          <IonToolbar className='fondoLluvia'>
            <ReactSVG src={Lluvia}></ReactSVG>
          </IonToolbar>
        </IonHeader>


      <IonContent fullscreen className='fondo'>

        <h2 className='texto'>Con nuestra función de control basada en la lluvia, puedes decidir cómo quieres que tus dispositivos respondan cuando detecten lluvia.</h2>
        <IonCheckbox className='checkbox' checked={isChecked} onIonChange={guardar}>Cerrar en caso de lluvia</IonCheckbox>
        <ReactSVG src={Volver} className='imgAtras3' onClick={back}></ReactSVG>

      </IonContent>
    </IonPage>
  );
};

export default Home;

