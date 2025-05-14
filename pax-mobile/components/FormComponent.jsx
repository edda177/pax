import { Pressable, StyleSheet, Text, View, TextInput } from 'react-native'
import React from 'react'
import { useTheme } from '../theme/ThemeContext'


const FormComponent = ({ userName, setUsername, password, setPassword }) => {
    const { theme } = useTheme ();
    const styles = createStyles (theme);
  return (
    <View>
     <Text style={styles.label}>Användarnamn:</Text>
      <TextInput style={styles.input}
      value= {userName}
      onChangeText={setUsername}
      placeholder='Användarnamn'
       />
       <Text style={styles.label}>Lösenord:</Text>
        <TextInput
      style={styles.input}
      value={password}
      onChangeText={setPassword}
      secureTextEntry
       />
    </View>
  )
}


export default FormComponent


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
            fontFamily: 'NunitoSans',
          },
          input: {
            padding: 20,
            width: 300,
            backgroundColor: theme.card,
            borderRadius: 10,
            margin: 10,
          },
          button: {
            margin: 10,
            padding: 20,
            backgroundColor: theme.card,
            borderRadius: 20,
            width: 200,
            textAlign: 'right',
            alignSelf: 'flex-end',
            marginRight: 10,
            borderColor: theme.accent,
            borderWidth: 2,
            fontFamily: 'NunitoSans'
          },
          pressed: {
            color:'red',
          },
          buttonText: {
            color: theme.textPrimary,
            textAlign: 'center',
            fontSize: 20,
          }
     })
