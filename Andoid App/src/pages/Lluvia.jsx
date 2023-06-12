import { IonContent, IonHeader, IonCheckbox, IonPage, IonToolbar } from '@ionic/react';
import './Lluvia.css';
import { ReactSVG } from 'react-svg';
import { BleClient, numbersToDataView } from '@capacitor-community/bluetooth-le';
import { useEffect, useState } from 'react';


import Lluvia from '../imagenes/titulolluvia.svg';
import Volver from '../imagenes/volver.svg'

function Home () {

  const HEART_RATE_SERVICE = '0000abcd-0000-1000-8000-00805f9b34fb';
  const READ_CHARACTERISTIC = "00001111-0000-1000-8000-00805F9B34FB";
  const WRITE_CHARACTERISTIC = "00001111-0000-1000-8000-00805F9B34FB";

  const [isChecked, setIsChecked] = useState(false);

  useEffect(() => {
    const interval = setInterval(async () => {
  
      const devices = await BleClient.getConnectedDevices([]);
      console.log('Dispositivos conectados:', devices);

      if(devices == 0){
        window.location.href ='/Dispositivos';
      }

    }, 3000);

    setTimeout(comprobar, 20);

    async function comprobar(){

      const devices = await BleClient.getConnectedDevices([]);
      console.log('Dispositivos conectados:', devices);

      devices.forEach(async (device) => {
        const estado = await BleClient.read(device.deviceId, HEART_RATE_SERVICE, READ_CHARACTERISTIC);
        console.log('ESTADO:', estado.getUint8(0));   
        if(estado.getUint8(0) == 0){
          setIsChecked(false)
        }else if(estado.getUint8(0) == 1){
          setIsChecked(true)
        }
      });
    }

  }, []);
  
  const guardar = async (event) => {
    
    setIsChecked(event.target.value);

    if(isChecked == false){
      setIsChecked(true);

      const devices = await BleClient.getConnectedDevices([]);
      console.log('Dispositivos conectados:', devices);

      devices.forEach(async (device) => {
        await BleClient.write(device.deviceId, HEART_RATE_SERVICE, WRITE_CHARACTERISTIC, numbersToDataView([1]));

      });


    }else if(isChecked == true){
      setIsChecked(false);

      const devices = await BleClient.getConnectedDevices([]);
      console.log('Dispositivos conectados:', devices);

      devices.forEach(async (device) => {
        await BleClient.write(device.deviceId, HEART_RATE_SERVICE, WRITE_CHARACTERISTIC, numbersToDataView([0]));

      });

      
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

