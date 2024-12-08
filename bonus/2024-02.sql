-- clickhouse local --queries-file bonus/2024-02.sql
with (
    --- input
    arrayMap(x -> toInt16(x), splitByChar(' ', c1)) as report,
    --- part1
    arrayPopFront(arrayDifference(report)) as deltas,
    not arrayExists(x -> abs(x) > 3, deltas)
    and (
        arrayAll(x -> x > 0, deltas)
        or arrayAll(x -> x < 0, deltas)
    ) as valid,
    --- part2
    arrayEnumerate(report) as idxs,
    arrayMap(
        i -> arrayFilter((_, j) -> i != j, report, idxs),
        idxs
    ) as possibleReports,
    arrayMap(
        report -> arrayPopFront(arrayDifference(report)),
        possibleReports
    ) as possibleDeltas,
    arrayExists(
        deltas -> (
            not arrayExists(x -> abs(x) > 3, deltas)
            and (
                arrayAll(x -> x > 0, deltas)
                or arrayAll(x -> x < 0, deltas)
            )
        ),
        possibleDeltas
    ) as fixable
)
select
    countIf(valid) as part1,
    countIf(valid or fixable) as part2
from
    file('testdata/2024-02.txt', 'LineAsString', 'c1 String');
