import { StyleSheet, Text, View } from 'react-native'
import React, { useState } from 'react'
import { useTheme } from '../theme/ThemeContext';
import LogoComponent from '../components/logoComponent';

const Login = ({ navigation }) => {
    const { theme } = useTheme ();
    const { userName, saveUserName } = useUser();
    const styles = createStyles (theme);

    const [ name, setName ] = useState("");

    const [ error, setError ] = useState("");

    const { login } = useAuth(); 

    const handleSubmit = () => {
        if (name.trim() .length <2) {
            setError("Namnet måste bestå av minst 2 tecken.");
            console.log(error);
            return;
        }
        saveUserName(name.trim());

        const fakeToken = Math.random().toString(36).slice(2)
        // Använda logion funktionen från AuthContext
        // fakeToken ersätts senare av det token som erhålls från backend
        login(fakeToken);
        navigation.navigate("Home")
    }
  return (
    <View>
     <LogoComponent />
      <Text>Login</Text>
    </View>
  )
}

export default Login

const createStyles = (theme) => 
    StyleSheet.create({
        
    })