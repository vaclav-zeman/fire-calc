module Data = {
  type action =
    | Calculate(FormStore.Form.state);

  type state = {
    resultList: Finance.resultList,
    targetAmount: float,
    targetYear: option(int),
  };

  let initialState = {resultList: [], targetAmount: 0.0, targetYear: None};

  // 25x of yearly expenses is considered save for retiring for ordinary person
  let magicConstant = 25.0;

  let reducer = (_, action) =>
    switch (action) {
    | Calculate(formValues) =>
      let yearlySavings =
        Finance.savings(
          ~income=float_of_string(formValues.income),
          ~spending=float_of_string(formValues.spending),
        );
      let resultList: Finance.resultList =
        Finance.getResultList(
          ~rate=float_of_string(formValues.annualReturn),
          ~principal=float_of_string(formValues.currBalance),
          ~yearlySavings,
        );
      let targetAmount =
        float_of_string(formValues.spending) *. magicConstant;
      let targetYear =
        Finance.getFIREYear(~amounts=resultList, ~targetAmount);

      {targetAmount, resultList, targetYear};
    };
};