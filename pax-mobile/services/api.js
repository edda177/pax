const BASE_URL = "https://app.swaggerhub.com/apis-docs/alicegmn/pax-api/dev-oas3-new#/Auth/post_auth_login";

export const loginWithApi = async (userName, password) => {
    try {
        const response = await fetch(`${BASE_URL}`, {
            method: "POST",
            headers: { "Content-Type": "application/json", 
                'Accept' : 'application/json',
            },
            body: JSON.stringify({ 
                userName,
                password })
        });

        if (!response.ok) throw new Error("Inloggningen misslyckades");

        return await response.json(); // Innehåller tokens
    } catch(error) {
        console.error("Login error", error);
        return null;
    }
};

export const fetchUserProfile = async (token) => {
    try {
        const response = await fetch(`${BASE_URL}`, {
            method: "GET",
            headers: {
                Authorization: `Bearer ${token}`
            }
        });

        if (!response.ok) throw new Error("Kunde inte hämta profil");

        return await response.json();
    } catch (error) {
        console.log("Fetch user error", error);
        return null;
    }
}