import { StyleSheet, Text, View, TextInput, Pressable} from 'react-native'
import React, { useState } from 'react'
import { useTheme } from '../theme/ThemeContext';
import LogoComponent from '../components/LogoComponent';

const Login = ({ navigation }) => {
    const { theme } = useTheme ();
    // const { userName, saveUserName } = useUser();
    const styles = createStyles (theme);

    const [ name, setName ] = useState("");

    const [ error, setError ] = useState("");

    // const { login } = useAuth(); 

    const handleSubmit = () => {
        if (name.trim() .length <2) {
            setError("Namnet måste bestå av minst 2 tecken.");
            console.log(error);
            return;
        }
        saveUserName(name.trim());
      }

  return (
    <View style={styles.container}>
     <LogoComponent style={styles.logo} />
     <Text style={styles.label}>Användarnamn</Text>
     <TextInput
       value={name}
       onChangeText={(text) => {
        setName(text);
        setError("");
      }}
        style={styles.input}
        accessibilityLabel='Användarnamn'
        accessibilityHint='Fält där du kan skriva in ditt användarnamn'
        keyboardType='default'
        //   keyboardType för epost - "email-address"
        returnKeyType='done'
        // returnKey... utforska gärna andra alternativ
        />

         {error ? <Text>{error}</Text> : null}
         <Text style={styles.label}>Lösenord</Text>
         <TextInput
       value={name}
       onChangeText={(text) => {
        setName(text);
        setError("");
      }}
        style={styles.input}
        accessibilityLabel='Lösenord'
        accessibilityHint='Fält där du kan skriva in ditt lösenord'
        keyboardType='default'
        //   keyboardType för epost - "email-address"
        returnKeyType='done'
        // returnKey... utforska gärna andra alternativ
        />

        <Pressable
          onPress={handleSubmit}
          style={({ pressed }) => [styles.button, pressed && styles.pressed]}
          accessibilityRole='button'
          accessibilityLabel='Logga in knapp'
          accessibilityHint='Tryck här för att logga in med det angivna namnet'
         >
           <Text style={styles.buttonText}>Logga in</Text>
        </Pressable>
    </View>
  )
}

export default Login

const createStyles = (theme) => 
    StyleSheet.create({
      container: {
        flex: 1,
        backgroundColor: theme.background,
        paddingBottom: 0,
        paddingTop: 100,
      },
      logo: {
        marginTop: 80,
        alignSelf: 'center',

      },
      label: {
        fontSize: 20,
        textAlign: 'left',
        alignSelf: 'flex-start',
        marginLeft: 10,
        color: theme.textPrimary,

      },
      input: {
        padding: 20,
        width: 300,
        backgroundColor: theme.card,
        borderRadius: 10,
        margin: 10,
      },
      button: {
        padding: 20,
        backgroundColor: theme.card,
        borderRadius: 10,
        width: 200,
        textAlign: 'right',
        alignSelf: 'flex-end',
        marginRight: 50,
      },
      pressed: {
      },
      buttonText: {
        color: theme.textPrimary,
      }
    })