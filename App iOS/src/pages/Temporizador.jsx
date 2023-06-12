import { IonButton, IonContent, IonToolbar, IonHeader, IonLabel, IonPage, IonDatetime } from '@ionic/react';
import React, { useEffect, useState } from 'react';
import { ReactSVG } from 'react-svg';
import { BleClient, textToDataView } from '@capacitor-community/bluetooth-le';
import { BLE } from '@ionic-native/ble';

import './Temporizador.css';

import TituloTiempo from '../imagenes/titulotiempo.svg'
import Volver from '../imagenes/volver.svg'

const HEART_RATE_SERVICE = '0000abcd-0000-1000-8000-00805f9b34fb';
const WRITE_CHARACTERISTIC2 = "00004321-0000-1000-8000-00805F9B34FB"

function Home () {

  const [currentTime, setCurrentTime] = useState('');
  const [selectedDate, setSelectedDate] = useState(null);

  useEffect(() => {
    console.log(selectedDate);
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

    }, 2000);

    const getCurrentTime = () => {
      const date = new Date();
      const hours = date.getHours().toString().padStart(2, '0');
      const minutes = date.getMinutes().toString().padStart(2, '0');
      const seconds = date.getSeconds().toString().padStart(2, '0');
      const timeStr = `${hours}:${minutes}:${seconds}`;
      setCurrentTime(timeStr);
    };
    getCurrentTime();

    const interval2 = setInterval(() => {
      getCurrentTime();
    }, 30000);

    return () => {
      clearInterval(interval2);
    };

  }, []);

    const cambios = (event) => {
        setSelectedDate(event.target.value);
      };
    
    const abrir = () => {
      BLE.connectedPeripheralsWithServices([HEART_RATE_SERVICE]).then(
        async peripherals => {
          console.log('Dispositivos conectados con el servicio ' + HEART_RATE_SERVICE + ':');
          for(let i = 0; i < peripherals.length; i++) {
            console.log(peripherals[i].id);
            await BleClient.write(peripherals[i].id, HEART_RATE_SERVICE, WRITE_CHARACTERISTIC2, textToDataView(selectedDate.slice(11, 16) + " " + currentTime + " 1"));
          }
        },
        error => {
          console.log('Error al buscar dispositivos conectados: ' + error);
        }
      );
    };  

    const cerrar = () => {
      BLE.connectedPeripheralsWithServices([HEART_RATE_SERVICE]).then(
        async peripherals => {
          console.log('Dispositivos conectados con el servicio ' + HEART_RATE_SERVICE + ':');
          for(let i = 0; i < peripherals.length; i++) {
            console.log(peripherals[i].id);
            await BleClient.write(peripherals[i].id, HEART_RATE_SERVICE, WRITE_CHARACTERISTIC2, textToDataView(selectedDate.slice(11, 16) + " " + currentTime + " 0"));
          }
        },
        error => {
          console.log('Error al buscar dispositivos conectados: ' + error);
        }
      );    };  

  function back(){
    window.location.href ='/Menu';
  }

  function Mostrar(){

    if(selectedDate != null){
      return(
        <div className='contenedor-buttons'>
          <IonButton onClick={abrir} className='buttons' color='#797979'>Abrir</IonButton>
          <IonButton onClick={cerrar} className='buttons' color="var(--color-personalizado)">Cerrar</IonButton>
        </div>
      )
    }else{
      return(
        <h1 className='h2'>Ninguna hora seleccionada</h1>
      )
    }

  }

  return (
    <IonPage>
        <IonHeader className='fondoTiempo'>
          <IonToolbar className='fondoTiempo'>
            <ReactSVG src={TituloTiempo}></ReactSVG>
          </IonToolbar>
        </IonHeader>

      <IonContent fullscreen className='fondoTiempo'>

        <IonLabel className='tituloSeleccionar'>Seleccione una hora: </IonLabel>

        <IonDatetime presentation='time' value={selectedDate} onIonChange={cambios} className='timer'></IonDatetime>

        <Mostrar/>

        <ReactSVG src={Volver} className='imgAtras2' onClick={back}></ReactSVG>

      </IonContent>
    </IonPage>
  );
};

export default Home;