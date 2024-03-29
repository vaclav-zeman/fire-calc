// Generated by BUCKLESCRIPT VERSION 5.0.4, PLEASE EDIT WITH CARE
'use strict';


function updateFormState(state, field, value) {
  switch (field) {
    case 0 : 
        return /* record */[
                /* annualReturn */value,
                /* currBalance */state[/* currBalance */1],
                /* income */state[/* income */2],
                /* spending */state[/* spending */3],
                /* savingsRate */state[/* savingsRate */4],
                /* hasSubmitted */state[/* hasSubmitted */5]
              ];
    case 1 : 
        return /* record */[
                /* annualReturn */state[/* annualReturn */0],
                /* currBalance */value,
                /* income */state[/* income */2],
                /* spending */state[/* spending */3],
                /* savingsRate */state[/* savingsRate */4],
                /* hasSubmitted */state[/* hasSubmitted */5]
              ];
    case 2 : 
        return /* record */[
                /* annualReturn */state[/* annualReturn */0],
                /* currBalance */state[/* currBalance */1],
                /* income */value,
                /* spending */state[/* spending */3],
                /* savingsRate */state[/* savingsRate */4],
                /* hasSubmitted */state[/* hasSubmitted */5]
              ];
    case 3 : 
        return /* record */[
                /* annualReturn */state[/* annualReturn */0],
                /* currBalance */state[/* currBalance */1],
                /* income */state[/* income */2],
                /* spending */state[/* spending */3],
                /* savingsRate */value,
                /* hasSubmitted */state[/* hasSubmitted */5]
              ];
    case 4 : 
        return /* record */[
                /* annualReturn */state[/* annualReturn */0],
                /* currBalance */state[/* currBalance */1],
                /* income */state[/* income */2],
                /* spending */value,
                /* savingsRate */state[/* savingsRate */4],
                /* hasSubmitted */state[/* hasSubmitted */5]
              ];
    
  }
}

function reducer(state, action) {
  if (action) {
    return updateFormState(state, action[0], action[1]);
  } else {
    return /* record */[
            /* annualReturn */state[/* annualReturn */0],
            /* currBalance */state[/* currBalance */1],
            /* income */state[/* income */2],
            /* spending */state[/* spending */3],
            /* savingsRate */state[/* savingsRate */4],
            /* hasSubmitted */true
          ];
  }
}

var Form_000 = /* initialState : record */[
  /* annualReturn */"7",
  /* currBalance */"0",
  /* income */"360000",
  /* spending */"120000",
  /* savingsRate */"66",
  /* hasSubmitted */false
];

var Form = /* module */[
  Form_000,
  /* updateFormState */updateFormState,
  /* reducer */reducer
];

exports.Form = Form;
/* No side effect */
