import { ScrollView, StyleSheet, Text, View } from 'react-native';
import React, { useEffect, useState } from 'react';
import FormComponent from '../components/FormComponent';
import LogoComponent from '../components/LogoComponent';
import { useTheme } from '../theme/ThemeContext';
import ThemeToggleTabButton from '../components/ThemeToggleTabButton';
import ButtonComponent from '../components/buttons/ButtonComponent';
import { useNavigation } from '@react-navigation/native';

const LoginTest = () => {
  const { theme } = useTheme();
  const styles = createStyles(theme);
  const navigation = useNavigation();

  const [users, setUsers] = useState([]);
  const [username, setUsername] = useState('');
  const [password, setPassword] = useState('');
  const [error, setError] = useState('');

  // ✅ Fetchar användare när skärmen laddas
  useEffect(() => {
    const fetchUsers = async () => {
      try {
        const response = await fetch(
          'https://virtserver.swaggerhub.com/alicegmn/pax-api/dev-oas3-new/users'
        );
        const data = await response.json();
        setUsers(data);
      } catch (error) {
        console.error('Fel vid hämtning av användare:', error);
        setError('Kunde inte hämta användare');
      }
    };

    fetchUsers();
  }, []);

  const handleLogin = async () => {
    setError('');
    const user = users.find(
      (u) => u.username === username && u.password === password
    );

    if (user) {
      console.log('Inloggning lyckades:', user);
      navigation.navigate('HomeScreen'); // ändra till din riktiga skärmrubrik
    } else {
      setError('Fel användarnamn eller lösenord.');
    }
  };

  return (
    <ScrollView>
      <View style={styles.container}>
        <ThemeToggleTabButton />
        <LogoComponent style={styles.logo} />
        {/* 👇 Du behöver skicka in setUsername/setPassword till formuläret */}
        <FormComponent
          username={username}
          setUsername={setUsername}
          password={password}
          setPassword={setPassword}
        />
        <ButtonComponent
          title="Logga in"
          onPress={handleLogin}
          style={styles.button}
        />
        {error ? <Text style={styles.error}>{error}</Text> : null}
      </View>
    </ScrollView>
  );
};

export default LoginTest;

const createStyles = (theme) => 
    StyleSheet.create({
      container: {
        flex: 1,
        backgroundColor: theme.background,
        paddingBottom: 0,
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
        padding: 15,
        backgroundColor: theme.card,
        borderRadius: 10,
        width: 100,
        textAlign: 'right',
        alignSelf: 'flex-end',
        marginLeft: 50,
      },
      pressed: {
      },
    })